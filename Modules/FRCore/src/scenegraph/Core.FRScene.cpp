#include "Core.FRScene.h"

#include "Core.FRActor.h"
#include "Core.FRCompLight.h"
#include "Core.FRCompCamera.h"
#include "Core.FRCompTransform.h"
#include "Core.FRCompRendererable.h"
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

#include <algorithm>

FR::FRScene::FRScene()
{
	mScene = FRFilamentHelper::CreateScene();
}

void FR::FRScene::Playing()
{
	playing = true;

	//std::for_each(mActors.begin(), mActors.end(), [](FRActor* pElement) { if (pElement->IsActive()) pElement->OnAwake(); });
	std::for_each(mActors.begin(), mActors.end(), [](FRActor* pElement) { if (pElement->IsActive()) pElement->OnStart(); });
	std::for_each(mActors.begin(), mActors.end(), [](FRActor* pElement) { if (pElement->IsActive()) pElement->OnEnable(); });
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

FR::FRActor* FR::FRScene::CreateActor()
{
	return CreateActor("New Actor");
}

FR::FRActor* FR::FRScene::CreateActor(const std::string& pName, const std::string& pTag)
{
	mActors.push_back(new FRActor(pName, pTag));

	FRActor* actor = mActors.back();
	actor->ComponentAddedEvent += std::bind(&FRScene::OnComponentAdded, this, std::placeholders::_1);
	actor->ComponentRemovedEvent += std::bind(&FRScene::OnComponentRemoved, this, std::placeholders::_1);
	
	if (playing)
	{
		if (actor->IsActive())
		{
			actor->OnAwake();
			//actor->OnStart();
			//actor->OnEnable();
		}
	}

	return actor;
}

bool FR::FRScene::DestroyActor(FRActor* pTarget)
{
	auto found = std::find_if(mActors.begin(), mActors.end(), [pTarget](FRActor* pElement)
		{
			return pElement == pTarget;
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
				if (auto modelRenderer = pElement->GetComponent<FRCompRendererable>())
				{
					RemoveRenderable(&modelRenderer->GetRenderable());
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
	auto result = std::find_if(mActors.begin(), mActors.end(), [pName](FRActor* pElement)
		{
			return pElement->name== pName;
		});

	if (result != mActors.end())
	{
		return *result;
	}

	return nullptr;
}

FR::FRActor* FR::FRScene::FindActorByTag(const std::string& pTag) const
{
	auto result = std::find_if(mActors.begin(), mActors.end(), [pTag](FRActor* pElement)
		{
			return pElement->tag == pTag;
		});

	if (result != mActors.end())
	{
		return *result;
	}

	return nullptr;
}

FR::FRActor* FR::FRScene::FindActorByUUID(int64_t pUUID) const
{
	auto result = std::find_if(mActors.begin(), mActors.end(), [pUUID](FRActor* pElement)
		{
			return pElement->uUID == pUUID;
		});

	if (result != mActors.end())
	{
		return *result;
	}

	return nullptr;
}

std::vector<std::reference_wrapper<FR::FRActor>> FR::FRScene::FindActorsByName(const std::string& pName) const
{
	std::vector<std::reference_wrapper<FRActor>> actors;

	for (auto& actor : mActors)
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

	for (auto& actor : mActors)
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
	for (const auto& camera : mFastAccessComponents.cameras)
	{
		if (camera->owner.IsActive())
		{
			return camera;
		}
	}

	return nullptr;
}

void FR::FRScene::SetEnvironment(FREnvironment* pEnvironment)
{
	mEnvironment = pEnvironment;
	//mScene->SetSkybox(mEnvironment->GetSkybox());
	mScene->SetIndirectLight(mEnvironment->GetIndirectLight());
}

void FR::FRScene::OnComponentAdded(FRComponent* pCompononent)
{
	if (auto result = dynamic_cast<FRCompRendererable*>(pCompononent))
	{
		mFastAccessComponents.modelRenderers.push_back(result);
	}

	if (auto result = dynamic_cast<FRCompCamera*>(pCompononent))
	{
		mFastAccessComponents.cameras.push_back(result);
	}

	if (auto result = dynamic_cast<FRCompLight*>(pCompononent))
	{
		mFastAccessComponents.lights.push_back(result);
	}
}

void FR::FRScene::OnComponentRemoved(FRComponent* pCompononent)
{
	if (auto result = dynamic_cast<FRCompRendererable*>(pCompononent))
	{
		mFastAccessComponents.modelRenderers.erase(
			std::remove(mFastAccessComponents.modelRenderers.begin(), mFastAccessComponents.modelRenderers.end(), result),
			mFastAccessComponents.modelRenderers.end());
	}

	if (auto result = dynamic_cast<FRCompCamera*>(pCompononent))
	{
		mFastAccessComponents.cameras.erase(
			std::remove(mFastAccessComponents.cameras.begin(), mFastAccessComponents.cameras.end(), result),
			mFastAccessComponents.cameras.end());
	}

	if (auto result = dynamic_cast<FRCompLight*>(pCompononent))
	{
		mFastAccessComponents.lights.erase(
			std::remove(mFastAccessComponents.lights.begin(), mFastAccessComponents.lights.end(), result),
			mFastAccessComponents.lights.end());
	}
}

const std::vector<FR::FRActor*>& FR::FRScene::GetActors()
{
	return mActors;
}

const FR::FRScene::FastAccessComponents& FR::FRScene::GetFastAccessComponents() const
{
	return mFastAccessComponents;
}

void FR::FRScene::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pRoot)
{
	tinyxml2::XMLNode* sceneNode = pDoc.NewElement("scene");
	pRoot->InsertEndChild(sceneNode);

	tinyxml2::XMLNode* actorsNode = pDoc.NewElement("actors");
	sceneNode->InsertEndChild(actorsNode);

	for (auto& actor : mActors)
	{
		actor->OnSerialize(pDoc, actorsNode);
	}
}

void FR::FRScene::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pRoot)
{
	tinyxml2::XMLNode* actorsRoot = pRoot->FirstChildElement("actors");

	if (actorsRoot)
	{
		tinyxml2::XMLElement* currentActor = actorsRoot->FirstChildElement("actor");

		while (currentActor)
		{
			auto actor = CreateActor();
			actor->OnDeserialize(pDoc, currentActor);
			currentActor = currentActor->NextSiblingElement("actor");
		}

		for (auto actor : mActors)
		{
			if (actor->GetParentUUID() > 0)
			{
				if (auto found = FindActorByUUID(actor->GetParentUUID()))
				{
					actor->SetParent(found);
				}
			}
		}
	}
}

void FR::FRScene::ParseScene()
{
	auto components = GetFastAccessComponents();

	for (auto& modelRenderer : components.modelRenderers)
	{
		if (auto& owner = modelRenderer->owner; owner.IsActive())
		{
			auto& renderable = modelRenderer->GetRenderable();
			if (renderable.GetMeshes().size() > 0)
			{
				auto& transform = owner.transform->GetFRTransform();
				renderable.SetTransform(transform.GetLocalMatrix());

				const auto& meshes = renderable.GetMeshes();
				const auto& materials = renderable.GetMaterials();
				for (size_t i = 0; i < meshes.size(); i++)
				{
					if (auto material = materials[i])
					{
						material->UploadData();
					}
				}
			}
		}
	}

	for (FRCompLight* light : components.lights)
	{
		if (auto& owner = light->owner; owner.IsActive())
		{
			light->GetLight().UploadData();
		}
	}
}

void FR::FRScene::AddLight(FRLight* pLight)
{
	mScene->AddEntity(pLight->GetEntity()->NatrivePtr());
}

void FR::FRScene::AddGizmo(FRRenderable* pRenderable)
{
	for (const auto& entity : pRenderable->GetNativePtrs())
	{
		mScene->AddEntity(entity);
	}
}

void FR::FRScene::AddRenderable(FRRenderable* pRenderable)
{
	for (const auto& entity : pRenderable->GetNativePtrs())
	{
		mScene->AddEntity(entity);
	}
}

void FR::FRScene::RemoveRenderable(FRRenderable* pRenderable)
{
	for (const auto& entity : pRenderable->GetNativePtrs())
	{
		mScene->Remove(entity);
	}
}

void FR::FRScene::RemoveLight(FRLight* pLight)
{
	mScene->Remove(pLight->GetEntity()->NatrivePtr());
}

FR::FRSceneWarp* FR::FRScene::NativePtr()
{
	return mScene;
}

FR::FRScene::~FRScene()
{
	for (auto& actor : mActors)
	{
		delete actor; actor = nullptr;
	}
	mActors.clear();

	FRFilamentHelper::GetEngine()->Destroy(mScene);
}