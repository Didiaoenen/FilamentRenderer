#include "Core.FRCompModelRenderer.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"
#include "Core.FRActor.h"
#include "Core.FRMaterial.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRModelManager.h"
#include "Core.FRMaterialManager.h"
#include "Core.FRCompMaterialRenderer.h"

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

FR::FRCompModelRenderer::FRCompModelRenderer(FRActor& pOwner)
	: FRComponent(pOwner)
{
	mMeshFields.fill(nullptr);
	mMaterialFields.fill(nullptr);

	mModelChangedEvent += [this]
		{
			//if (auto materialRenderer = owner.GetComponent<CMaterialRenderer>())
			//{
			//	materialRenderer->UpdateMaterialList();
			//}
		};
}

const std::string FR::FRCompModelRenderer::GetName()
{
	return ICON_MDI_GRID " Model Renderer";
}

FR::FRComponent::EComponentType FR::FRCompModelRenderer::GetType()
{
	return FRComponent::EComponentType::MODEL_RENDERER;
}

void FR::FRCompModelRenderer::SetModel(FRModel* pModel)
{
	mModel = pModel;

	mEntities.emplace_back(FRFilamentHelper::CreateEntity());

	mModel->Build(mEntities.back());

	if (auto scene = owner.GetScene())
	{
		for (const auto& mesh : mModel->GetMeshes())
		{
			mEntities.emplace_back(FRFilamentHelper::CreateEntity());
			mesh->Build(mEntities.back());
		}
		scene->AddModel(pModel);
	}

	mModelChangedEvent.Invoke();
}

FR::FRModel* FR::FRCompModelRenderer::GetModel() const
{
	return mModel;
}

void FR::FRCompModelRenderer::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompModelRenderer::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompModelRenderer::OnInspector(GUI::FRWidgetContainer& pRoot)
{
	FRGuiDrawer::CreateTitle(pRoot, "Model").lineBreak = false;

	auto& pData = mModel;
	auto* pUpdateNotifier = &mModelChangedEvent;

	std::string displayedText = (pData ? pData->path : std::string("Empty"));

	auto& itemSelect = pRoot.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MODEL, displayedText);
	itemSelect.SetTextReceivedEvent([&pData, pUpdateNotifier, this](std::string& pContext, auto pReceivedData)
		{
			if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MODEL)
			{
				if (auto resource = GetService(FRModelManager).GetResource(pReceivedData.first); resource)
				{
					//pData = resource;

					//owner.GetScene()->RemoveModel(pData);
					//owner.GetScene()->AddModel(resource);

					pContext = pReceivedData.first;
					if (pUpdateNotifier)
					{
						pUpdateNotifier->Invoke();
					}
				}
			}
		});

	auto& widgetMeshes = pRoot.CreateWidget<FRTreeNode>("Meshes", "", "", true);
	for (uint8_t i = 0; i < pData->GetMeshes().size(); i++)
	{
		auto mesh = pData->GetMeshes()[i];
		auto& widgetMesh = widgetMeshes.CreateWidget<FRTextColored>(mesh->name);
		widgetMesh.position = { 60.0f, 0.0f };
		mMeshFields[i] = &widgetMesh;
	}
	widgetMeshes.framed = true;
	widgetMeshes.position = { 30.0f, 0.0f };

	auto& widgetMaterials = pRoot.CreateWidget<FRTreeNode>("Materials", "", "", true);
	for (uint8_t i = 0; i < pData->GetMeshes().size(); i++)
	{
		auto material = pData->GetMaterials()[i];
		auto& widgetMaterial = widgetMaterials.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MATERIAL, material->path);
		widgetMaterial.SetTextReceivedEvent([&pData, i, this](std::string& pContext, auto pReceivedData)
			{
				if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MATERIAL)
				{
					if (auto resource = GetService(FRMaterialManager).GetResource(pReceivedData.first))
					{
						pData->SetMaterialAtIndex(i, resource);
						pContext = pReceivedData.first;
					}
				}
			});

		mMaterialFields[i] = &widgetMaterial;
	}
	widgetMaterials.framed = true;
	widgetMaterials.position = { 30.f, 0.f };

	for (uint8_t i = 0; i < kMaxCount; ++i)
	{
		if (i >= pData->GetMeshes().size())
		{
			if (mMeshFields[i])
			{
				mMeshFields[i]->enabled = false;
			}

			if (mMaterialFields[i])
			{
				mMaterialFields[i]->enabled = false;
			}
		}
	}
}

FR::FRCompModelRenderer::~FRCompModelRenderer()
{
	for (const auto& entity : mEntities)
	{
		FRFilamentHelper::DestroyEntity(entity);
	}
	mEntities.clear();

	delete mModel;
}