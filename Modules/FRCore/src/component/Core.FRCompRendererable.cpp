#include "Core.FRCompRendererable.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"
#include "Core.FRActor.h"
#include "Core.FRMaterial.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRModelManager.h"
#include "Core.FRMaterialManager.h"

#include <FREntityManagerWarp.h>

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

FR::FRCompRendererable::FRCompRendererable(FRActor& pOwner)
	: FRComponent(pOwner)
	, mRenderable(&pOwner)
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

void FR::FRCompRendererable::SetRenderable(FRModel* pModel)
{
	mModelPath = pModel->path;

	for (auto& mesh : pModel->GetMeshes())
	{
		mRenderable.BuildMesh(mesh);
	}

	if (auto scene = owner.GetScene())
	{
		scene->AddRenderable(&mRenderable);
	}

	mModelChangedEvent.Invoke();
}

void FR::FRCompRendererable::FillMaterials(FRMaterial* pMaterial)
{
	mRenderable.FillMaterials(pMaterial);
}

void FR::FRCompRendererable::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompRendererable::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompRendererable::OnInspector(GUI::FRWidgetContainer& pRoot)
{
	FRGuiDrawer::CreateTitle(pRoot, "Model").lineBreak = false;

	auto* pUpdateNotifier = &mModelChangedEvent;

	std::string displayedText = (!mModelPath.empty() ? mModelPath : std::string("Empty"));

	auto& itemSelect = pRoot.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MODEL, displayedText);
	itemSelect.SetTextReceivedEvent([pUpdateNotifier, this](std::string& pContext, auto pReceivedData)
		{
			if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MODEL)
			{
				if (auto resource = GetService(FRModelManager).GetResource(pReceivedData.first))
				{
					pContext = pReceivedData.first;
					if (pUpdateNotifier)
					{
						pUpdateNotifier->Invoke();
					}
				}
			}
		});

	auto& widgetMeshes = pRoot.CreateWidget<FRTreeNode>("Meshes", "", "", true);
	for (uint8_t i = 0; i < mRenderable.GetMeshes().size(); i++)
	{
		auto mesh = mRenderable.GetMeshes()[i];
		auto& widgetMesh = widgetMeshes.CreateWidget<FRTextColored>(mesh->name);
		widgetMesh.position = { 60.0f, 0.0f };
		mMeshFields[i] = &widgetMesh;
	}
	widgetMeshes.framed = true;
	widgetMeshes.position = { 30.0f, 0.0f };

	auto& widgetMaterials = pRoot.CreateWidget<FRTreeNode>("Materials", "", "", true);
	for (uint8_t i = 0; i < mRenderable.GetMeshes().size(); i++)
	{
		auto material = mRenderable.GetMaterials()[i];
		auto& widgetMaterial = widgetMaterials.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MATERIAL, material->path);
		widgetMaterial.SetTextReceivedEvent([i, this](std::string& pContext, auto pReceivedData)
			{
				if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MATERIAL)
				{
					if (auto resource = GetService(FRMaterialManager).GetResource(pReceivedData.first))
					{
						mRenderable.SetMaterialAtIndex(i, resource);
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
		if (i >= mRenderable.GetMeshes().size())
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

const std::string FR::FRCompRendererable::GetName()
{
	return ICON_MDI_GRID " Rendererable";
}

FR::FRComponent::EComponentType FR::FRCompRendererable::GetType()
{
	return FRComponent::EComponentType::MODEL_RENDERER;
}

FR::FRRenderable& FR::FRCompRendererable::GetRenderable()
{
	return mRenderable;
}

FR::FRCompRendererable::~FRCompRendererable() = default;