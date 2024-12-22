#pragma once

#include <array>
#include "Core.FRComponent.h"

namespace FR
{
	class FRMaterial;

	constexpr uint8_t kMaxMaterialCount = 0xFF;
	using MaterialList = std::array<FRMaterial*, kMaxMaterialCount>;
	using MaterialField = std::array<std::array<GUI::FRAWidget*, 3>, kMaxMaterialCount>;

	class FRCompMaterialRenderer
		: public FRComponent
	{
	public:
		FRCompMaterialRenderer(FRActor& pOwner);

		void FillWithMaterial(FRMaterial& pMaterial);

		void SetMaterialAtIndex(uint8_t pIndex, FRMaterial& pMaterial);

		FRMaterial* GetMaterialAtIndex(uint8_t pIndex);

		void RemoveMaterialAtIndex(uint8_t pIndex);

		void RemoveMaterialByInstance(FRMaterial& pInstance);

		void RemoveAllMaterials();

		void UpdateMaterialList();

		const MaterialList& GetMaterials() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

	private:
		void UpdateMaterial();

		void MaterialDrawer(GUI::FRWidgetContainer& pRoot, uint32_t pIndex, const std::string& pName, FRMaterial*& pData);

	private:
		MaterialList mMaterials;
		MaterialField mMaterialFields;
		std::array<std::string, kMaxMaterialCount> mMaterialNames;

	};
}

