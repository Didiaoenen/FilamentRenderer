#include "Core.FRCompMaterialRenderer.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"
#include "Core.FRActor.h"
#include "Core.FRMaterial.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRMaterialManager.h"
#include "Core.FRCompModelRenderer.h"

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

FR::FRCompMaterialRenderer::FRCompMaterialRenderer(FRActor& pOwner)
	: FRComponent(pOwner)
{
	mMaterials.fill(nullptr);

	for (uint8_t i = 0; i < kMaxMaterialCount; ++i)
	{
		mMaterialFields[i].fill(nullptr);
	}

	UpdateMaterialList();
}

const std::string FR::FRCompMaterialRenderer::GetName()
{
	return ICON_MDI_REACT " Material Renderer";
}

FR::FRComponent::EComponentType FR::FRCompMaterialRenderer::GetType()
{
	return FRComponent::EComponentType::MATERIAL_RENDERER;
}

void FR::FRCompMaterialRenderer::FillWithMaterial(FRMaterial& pMaterial)
{
	if (auto modelRenderer = owner.GetComponent<FRCompModelRenderer>())
	{
		if (auto model = modelRenderer->GetModel())
		{
			auto meshs = model->GetMeshes();
			for (size_t i = 0; i < meshs.size(); ++i)
			{
				mMaterials[i] = &pMaterial;
				meshs[i]->SetMaterial(&pMaterial);
			}
		}
	}
}

void FR::FRCompMaterialRenderer::SetMaterialAtIndex(uint8_t pIndex, FRMaterial& pMaterial)
{
	mMaterials[pIndex] = &pMaterial;
}

FR::FRMaterial* FR::FRCompMaterialRenderer::GetMaterialAtIndex(uint8_t pIndex)
{
	return mMaterials.at(pIndex);
}

void FR::FRCompMaterialRenderer::RemoveMaterialAtIndex(uint8_t pIndex)
{
	if (pIndex < mMaterials.size())
	{
		mMaterials[pIndex] = nullptr;
	}
}

void FR::FRCompMaterialRenderer::RemoveMaterialByInstance(FRMaterial& pInstance)
{
	for (uint8_t i = 0; i < mMaterials.size(); ++i)
	{
		if (mMaterials[i] == &pInstance)
		{
			mMaterials[i] = nullptr;
		}
	}
}

void FR::FRCompMaterialRenderer::RemoveAllMaterials()
{
	for (uint8_t i = 0; i < mMaterials.size(); ++i)
	{
		mMaterials[i] = nullptr;
	}
}

void FR::FRCompMaterialRenderer::UpdateMaterialList()
{
	if (auto modelRenderer = owner.GetComponent<FRCompModelRenderer>())
	{
		auto model = modelRenderer->GetModel();
		auto materialNames = model->GetMaterialNames();
		if (model && materialNames.size() > 0)
		{
			auto meshs = model->GetMeshes();
			for (uint8_t i = 0; i < kMaxMaterialCount; ++i)
			{
				if (i < meshs.size())
				{
					mMaterialNames[i] = materialNames[meshs[i]->materialIndex];
				}
				else
				{
					mMaterialNames[i] = "";
				}
			}
		}
	}

	for (uint8_t i = 0; i < mMaterialFields.size(); ++i)
	{
		if (mMaterialFields[i][0])
		{
			bool enabled = !mMaterialNames[i].empty();
			mMaterialFields[i][0]->enabled = enabled;
			dynamic_cast<FRText*>(mMaterialFields[i][0])->content = mMaterialNames[i];
		}
	}
}

const FR::MaterialList& FR::FRCompMaterialRenderer::GetMaterials() const
{
	return mMaterials;
}

void FR::FRCompMaterialRenderer::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompMaterialRenderer::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompMaterialRenderer::OnInspector(GUI::FRWidgetContainer& pRoot)
{
	if (auto modelRenderer = owner.GetComponent<FRCompModelRenderer>())
	{
		if (auto model = modelRenderer->GetModel())
		{
			auto meshs = model->GetMeshes();
			for (uint8_t i = 0; i < meshs.size(); ++i)
			{
				MaterialDrawer(pRoot, i, "Material", mMaterials[i]);
			}
		}
	}

	UpdateMaterialList();
}

void FR::FRCompMaterialRenderer::UpdateMaterial()
{
	if (auto modelRenderer = owner.GetComponent<FRCompModelRenderer>())
	{
		if (auto model = modelRenderer->GetModel())
		{
			auto meshs = model->GetMeshes();
			for (size_t i = 0; i < meshs.size(); ++i)
			{
				meshs[i]->SetMaterial(mMaterials[i]);
			}
		}
	}
}

void FR::FRCompMaterialRenderer::MaterialDrawer(GUI::FRWidgetContainer& pRoot, uint32_t pIndex, const std::string& pName, FRMaterial*& pData)
{
	FRGuiDrawer::CreateTitle(pRoot, "Element " + std::to_string(pIndex)).lineBreak = false;

	auto& itemSelect = pRoot.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MATERIAL, "");
	itemSelect.SetTextReceivedEvent([&pData, this](std::string& pContext, auto pReceivedData)
		{
			if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MATERIAL)
			{
				if (auto resource = GetService(FRMaterialManager).GetResource(pReceivedData.first))
				{
					pData = resource;
					pContext = pReceivedData.first;

					UpdateMaterial();
				}
			}
		});

	mMaterialFields[pIndex][0] = itemSelect.GetText();
}