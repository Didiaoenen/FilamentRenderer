#pragma once

#include "Core.FRComponent.h"

namespace FR
{
	class AnimationClip;

	class FRCompAniTest
		: public FRComponent
	{
	public:
		FRCompAniTest(FRActor& pOwner);

		virtual void OnStart() override;

		virtual void OnUpdate(float pDeltaTime) override;

		void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		const std::string GetName() override;

		EComponentType GetType() override;

	private:
		void DataReceivedChangeCallback(std::string& pContext, std::pair<std::string, GUI::FRGroup*> pDataReceived, int pIndex);

	public:
		virtual ~FRCompAniTest() = default;

	private:
		std::vector<AnimationClip*> mClips;

	};
}