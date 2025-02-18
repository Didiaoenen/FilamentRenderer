#pragma once

#include "AMotion.h"
#include "Animator.h"
#include "Core.FRComponent.h"

namespace FR
{
	class SkeletonRig;

	class FRCompAnimator
		: public FRComponent
	{
	public:
		FRCompAnimator(FRActor& pOwner);

		virtual void OnStart() override;

		virtual void OnUpdate(float pDeltaTime) override;

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

	public:
		~FRCompAnimator() = default;

	private:
		void DataReceivedChangeCallback(std::string& pContext, std::pair<std::string, GUI::FRGroup*> pDataReceived, int pIndex);

	private:
		Animator mAnimator;

		std::vector<AMotion*> mMotions;

		SkeletonRig* mSkeletonRig{ nullptr };

	};
}

