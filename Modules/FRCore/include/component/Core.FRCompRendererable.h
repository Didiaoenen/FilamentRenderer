#pragma once

#include "Core.FRComponent.h"
#include "Core.FRRenderable.h"

#include <array>

namespace FR
{
	class FRCompRendererable
		: public FRComponent
	{
		static constexpr uint8_t kMaxCount = 0xFF;

	public:
		FRCompRendererable(FRActor& pOwner);

		void SetRenderable(FRModel* pModel);

		void FillMaterials(FRMaterial* pMaterial);

		//const BoundingSphere& GetCustomBoundingSphere() const;

		//void SetCustomBoundingSphere(const BoundingSphere& pBoundingSphere);

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

		FRRenderable& GetRenderable();

	public:
		virtual ~FRCompRendererable();

	private:
		FRRenderable mRenderable;

		//BoundingSphere mBoundingSphere{ {}, 1.0f };

		std::array<GUI::FRAWidget*, kMaxCount> mMeshFields;
		std::array<GUI::FRAWidget*, kMaxCount> mMaterialFields;

		std::string mModelPath;

		FREvent<> mModelChangedEvent;

	};
}

