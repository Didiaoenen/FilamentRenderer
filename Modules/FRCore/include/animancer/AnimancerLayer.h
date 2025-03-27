#pragma once

#include "AnimancerNode.h"

#include <any>

namespace FR
{
	class AnimationClip;
	class AnimancerState;
	class AnimancerPlayable;

	class AnimancerLayer
		: public AnimancerNode
	{
	public:
		using AnimancerNode::OnAddChild;
		using AnimancerNode::CreatePlayable;

		AnimancerLayer(AnimancerPlayable* pRoot, int pIndex);

		virtual void CreatePlayable(AnimationPlayable*& pPlayable);

		virtual AnimancerLayer* Layer() override;

		virtual IPlayableWarp* Parent() override;

		AnimancerState* CurrentState();

		void SetCurrentState(AnimancerState* pState);

		void AddChild(AnimancerState* pState);

		virtual void OnAddChild(AnimancerState* pState) override;

		virtual void OnRemoveChild(AnimancerState* pState) override;

		AnimancerState* CreateState(AnimationClip* pClip);

		AnimancerState* CreateState(std::any pKey, AnimationClip* pClip);

		AnimancerState* GetState(std::any& pKey);

		AnimancerState* GetOrCreateState(AnimancerState* pState);

		AnimancerState* GetOrCreateState(AnimationClip* pClip, bool pAllowSetClip = false);

		AnimancerState* GetOrCreateState(std::any pKey, AnimationClip* pClip, bool pAllowSetClip = false);

		AnimancerState* Play(AnimationClip* pClip);

		AnimancerState* Play(AnimancerState* pState);

		AnimancerState* Play(AnimationClip* pClip, float pFadeDuration);

		AnimancerState* Play(AnimancerState* pState, float pFadeDuration);

	protected:
		virtual void OnStartFade() override;

	public:
		virtual ~AnimancerLayer();

	private:
		AnimancerState* mCurrState{ nullptr };

		std::vector<AnimancerState*> mStates;

	};
}