#include "Core.FRScene.h"

#include "Core.FRActor.h"
#include "Core.FRCompLight.h"
#include "Core.FRCompCamera.h"
#include "Core.FRCompTransform.h"
#include "Core.FRCompModelRenderer.h"
#include "Core.FREngineDrawableDescriptor.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"
#include "Core.FRLight.h"
#include "Core.FRMaterial.h"
#include "Core.FREnvironment.h"
#include "Core.FRDrawable.h"

#include <FRSceneWarp.h>
#include <FRSkyboxWarp.h>
#include <FRFilamentHelper.h>

#include <Tools.FRTimer.h>
#include <Tools.FRPathUtils.h>

#include <utils/Path.h>
#include <filament/Skybox.h>
#include <filament/IndirectLight.h>

#include <algorithm>

FR::FRScene::FRScene()
{
	mScene = FRFilamentHelper::CreateScene();
}

void FR::FRScene::Playing()
{
	playing = true;

	std::for_each(mActors.begin(), mActors.end(), [](FRActor* pElement) { if (pElement->IsActive()) pElement->OnAwake(); });
	std::for_each(mActors.begin(), mActors.end(), [](FRActor* pElement) { if (pElement->IsActive()) pElement->OnEnable(); });
	std::for_each(mActors.begin(), mActors.end(), [](FRActor* pElement) { if (pElement->IsActive()) pElement->OnStart(); });
}

void FR::FRScene::Update()
{
	std::for_each(mActors.begin(), mActors.end(), std::bind(std::mem_fn(&FRActor::OnUpdate), std::placeholders::_1, FRTimer::GetDeltaTimeSec()));
}

void FR::FRScene::LateUpdate()
{
	std::for_each(mActors.begin(), mActors.end(), std::bind(std::mem_fn(&FRActor::OnLateUpdate), std::placeholders::_1, FRTimer::GetDeltaTimeSec()));
}

void FR::FRScene::FixedUpdate()
{
	std::for_each(mActors.begin(), mActors.end(), std::bind(std::mem_fn(&FRActor::OnFixedUpdate), std::placeholders::_1, FRTimer::GetDeltaTimeSec()));
}

FR::FRActor& FR::FRScene::CreateActor()
{
	return CreateActor("New Actor");
}

FR::FRActor& FR::FRScene::CreateActor(const std::string& pName, const std::string& pTag)
{
	mActors.push_back(new FRActor(this, pName, pTag));
	FRActor& instance = *mActors.back();
	instance.ComponentAddedEvent += std::bind(&FRScene::OnComponentAdded, this, std::placeholders::_1);
	instance.ComponentRemovedEvent += std::bind(&FRScene::OnComponentRemoved, this, std::placeholders::_1);
	
	if (playing)
	{
		if (instance.IsActive())
		{
			instance.OnAwake();
			instance.OnEnable();
			instance.OnStart();
		}
	}
	return instance;
}

bool FR::FRScene::DestroyActor(FRActor& pTarget)
{
	auto found = std::find_if(mActors.begin(), mActors.end(), [&pTarget](FRActor* element)
		{
			return element == &pTarget;
		});

	if (found != mActors.end())
	{
		mActors.erase(found);
		delete *found;
		return true;
	}
	return false;
}

void FR::FRScene::CollectGarbages()
{
	mActors.erase(std::remove_if(mActors.begin(), mActors.end(), [this](FRActor* pElement)
		{
			if (bool isGarbage = !pElement->IsAlive())
			{
				auto modelRenderer = pElement->GetComponent<FRCompModelRenderer>();
				if (modelRenderer && modelRenderer->GetModel())
				{
					RemoveModel(modelRenderer->GetModel());
				}

				if (auto light = pElement->GetComponent<FRCompLight>())
				{
					RemoveLight(&light->GetLight());
				}

				delete pElement;
				return true;
			}
			return false;
		}), mActors.end());
}

FR::FRActor* FR::FRScene::FindActorByName(const std::string& pName) const
{
	auto result = std::find_if(mActors.begin(), mActors.end(), [pName](FRActor* element)
		{
			return element->name== pName;
		});

	if (result != mActors.end())
	{
		return *result;
	}
	return nullptr;
}

FR::FRActor* FR::FRScene::FindActorByTag(const std::string& pTag) const
{
	auto result = std::find_if(mActors.begin(), mActors.end(), [pTag](FRActor* element)
		{
			return element->tag == pTag;
		});

	if (result != mActors.end())
	{
		return *result;
	}
	return nullptr;
}

FR::FRActor* FR::FRScene::FindActorByID(int64_t pID) const
{
	//auto result = std::find_if(mActors.begin(), mActors.end(), [pID](Actor* element)
	//	{
	//		return element->GetID() == pID;
	//	});

	//if (result != mActors.end())
	//{
	//	return *result;
	//}
	return nullptr;
}

std::vector<std::reference_wrapper<FR::FRActor>> FR::FRScene::FindActorsByName(const std::string& pName) const
{
	std::vector<std::reference_wrapper<FRActor>> actors;

	for (auto actor : mActors)
	{
		if (actor->name == pName)
		{
			actors.push_back(std::ref(*actor));
		}
	}
	return actors;
}

std::vector<std::reference_wrapper<FR::FRActor>> FR::FRScene::FindActorsByTag(const std::string& pTag) const
{
	std::vector<std::reference_wrapper<FRActor>> actors;

	for (auto actor : mActors)
	{
		if (actor->tag == pTag)
		{
			actors.push_back(std::ref(*actor));
		}
	}
	return actors;
}

FR::FRCompCamera* FR::FRScene::FindMainCamera() const
{
	for (FRCompCamera* camera : mFastAccessComponents.cameras)
	{
		if (camera->owner.IsActive())
		{
			return camera;
		}
	}
	return nullptr;
}

void FR::FRScene::OnComponentAdded(FRComponent& pCompononent)
{
	if (auto result = dynamic_cast<FRCompModelRenderer*>(&pCompononent))
	{
		mFastAccessComponents.modelRenderers.push_back(result);
	}

	if (auto result = dynamic_cast<FRCompCamera*>(&pCompononent))
	{
		mFastAccessComponents.cameras.push_back(result);
	}

	if (auto result = dynamic_cast<FRCompLight*>(&pCompononent))
	{
		mFastAccessComponents.lights.push_back(result);
	}
}

void FR::FRScene::OnComponentRemoved(FRComponent& pCompononent)
{
	if (auto result = dynamic_cast<FRCompModelRenderer*>(&pCompononent))
	{
		mFastAccessComponents.modelRenderers.erase(std::remove(mFastAccessComponents.modelRenderers.begin(), mFastAccessComponents.modelRenderers.end(), result), mFastAccessComponents.modelRenderers.end());
	}

	if (auto result = dynamic_cast<FRCompCamera*>(&pCompononent))
	{
		for (const auto camera : mFastAccessComponents.cameras)
		{
			FRFilamentHelper::DestroyEntity(camera->GetCamera().GetEntity());
		}
		mFastAccessComponents.cameras.erase(std::remove(mFastAccessComponents.cameras.begin(), mFastAccessComponents.cameras.end(), result), mFastAccessComponents.cameras.end());
	}

	if (auto result = dynamic_cast<FRCompLight*>(&pCompononent))
	{
		for (const auto light : mFastAccessComponents.lights)
		{
			FRFilamentHelper::DestroyEntity(light->GetLight().GetEntity());
		}
		mFastAccessComponents.lights.erase(std::remove(mFastAccessComponents.lights.begin(), mFastAccessComponents.lights.end(), result), mFastAccessComponents.lights.end());
	}
}

std::vector<FR::FRActor*>& FR::FRScene::GetActors()
{
	return mActors;
}

const FR::FRScene::FastAccessComponents& FR::FRScene::GetFastAccessComponents() const
{
	return mFastAccessComponents;
}

void FR::FRScene::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pRoot)
{

}

void FR::FRScene::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pRoot)
{

}

void FR::FRScene::ParseScene()
{
	std::vector<FR::FRDrawable> drawables;
	auto components = GetFastAccessComponents();
	for (FRCompModelRenderer* modelRenderer : components.modelRenderers)
	{
		auto& owner = modelRenderer->owner;

		if (owner.IsActive())
		{
			if (auto model = modelRenderer->GetModel())
			{
				auto& transform = owner.transform.GetFRTransform();

				auto meshes = model->GetMeshes();

				if (!meshes.empty())
				{
					auto& materials = model->GetMaterials();

					int index = 0;
					for (const auto& mesh : meshes)
					{
						if (auto material = materials[index++]; material)
						{
							FRDrawable drawable;
							drawable.mesh = mesh;
							drawable.material = material;
							drawable.AddDescriptor<FREngineDrawableDescriptor>({ transform.GetWorldMatrix() });

							drawables.emplace_back(drawable);
						}
					}
				}
			}
		}
	}

	for (FRCompLight* light : components.lights)
	{
		light->GetLight().UploadData();
	}

	for (const auto& drawable : drawables)
	{
		drawable.material.value().UploadData();
		FROptRef<const FREngineDrawableDescriptor> descriptor;
		if (drawable.TryGetDescriptor<FREngineDrawableDescriptor>(descriptor))
		{
			drawable.mesh.value().SetTransform(descriptor->modelMatrix);
		}
	}
}

void FR::FRScene::AddGizmo(FRModel* pGizmo)
{
	for (const auto mesh : pGizmo->GetMeshes())
	{
		mScene->AddEntity(mesh->GetEntity());
	}

	mGizmoModels.push_back(pGizmo);
}

void FR::FRScene::AddModel(FRModel* pModel)
{
	for (const auto mesh : pModel->GetMeshes())
	{
		mScene->AddEntity(mesh->GetEntity());
	}
}

void FR::FRScene::AddLight(FRLight& pLight)
{
	mScene->AddEntity(pLight.GetEntity());
}

void FR::FRScene::SetEnvironment(FREnvironment* pEnvironment)
{
	mEnvironment = pEnvironment;
	mScene->SetSkybox(mEnvironment->GetSkybox());
	mScene->SetIndirectLight(mEnvironment->GetIndirectLight());
}

void FR::FRScene::RemoveModel(const FRModel* pModel)
{
	for (const auto mesh : pModel->GetMeshes())
	{
		mScene->Remove(mesh->GetEntity());
	}
}

void FR::FRScene::RemoveLight(const FRLight* pLight)
{
	mScene->Remove(pLight->GetEntity());
}

const std::vector<FR::FRModel*> FR::FRScene::GetGizmoModels() const
{
	return mGizmoModels;
}

FR::FRSceneWarp* FR::FRScene::NativePtr()
{
	return mScene;
}

FR::FRScene::~FRScene()
{
	std::for_each(mActors.begin(), mActors.end(), [this](FRActor* pElement)
		{
			delete pElement;
		});

	mActors.clear();

	FRFilamentHelper::GetEngine()->Destroy(mScene);
}