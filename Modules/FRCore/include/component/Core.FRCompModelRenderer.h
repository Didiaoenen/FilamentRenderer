#pragma once

#include "Core.FRComponent.h"

#include <array>

namespace FR
{
	class FRModel;
	class FREntityWarp;

	class FRCompModelRenderer
		: public FRComponent
	{
		static constexpr uint8_t kMaxCount = 0xFF;

	public:
		FRCompModelRenderer(FRActor& pOwner);

		void SetModel(FRModel* pModel);

		//const BoundingSphere& GetCustomBoundingSphere() const;

		//void SetCustomBoundingSphere(const BoundingSphere& pBoundingSphere);

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

		FRModel* GetModel() const;

	public:
		virtual ~FRCompModelRenderer();

	private:
		FRModel* mModel{ nullptr };
		std::vector<FREntityWarp*> mEntities;

		//BoundingSphere m_customBoundingSphere{ {}, 1.0f };

		std::array<GUI::FRAWidget*, kMaxCount> mMeshFields;
		std::array<GUI::FRAWidget*, kMaxCount> mMaterialFields;

		FREvent<> mModelChangedEvent;

	};
}

