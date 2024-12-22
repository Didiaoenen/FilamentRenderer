#pragma once

#include <array>
#include "Core.FRComponent.h"

namespace FR
{
	class FRModel;

	class FRCompModelRenderer
		: public FRComponent
	{
		const static uint8_t kMaxCount = 0xFF;

	public:
		FRCompModelRenderer(FRActor& pOwner);

		FRModel* GetModel() const;

		void SetModel(FRModel* pModel);

		//const BoundingSphere& GetCustomBoundingSphere() const;

		//void SetCustomBoundingSphere(const BoundingSphere& pBoundingSphere);

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

	private:
		FRModel* mModel{ nullptr };

		FREvent<> mModelChangedEvent;

		//BoundingSphere m_customBoundingSphere{ {}, 1.0f };

		std::array<GUI::FRAWidget*, kMaxCount> mMeshFields;
		std::array<GUI::FRAWidget*, kMaxCount> mMaterialFields;

	};
}

