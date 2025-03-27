#pragma once

#include "Core.FRComponent.h"

#include "AnimancerPlayable.h"

namespace FR
{
	class AnimationClip;
	class AnimancerState;

    class FRCompAnimancer
        : public FRComponent
    {
    public:
        FRCompAnimancer(FRActor& pOwner);

		virtual void OnStart() override;

		virtual void OnUpdate(float pDeltaTime) override;

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

		AnimancerState* Play(AnimationClip* pClip);

		AnimancerState* Play(AnimationClip* pClip, float pFadeDuration);

	public:
		virtual ~FRCompAnimancer();

	private:
		AnimancerPlayable mPlayable;

    };
}