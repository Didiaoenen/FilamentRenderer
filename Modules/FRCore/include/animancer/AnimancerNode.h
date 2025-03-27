#pragma once

#include "ICopyable.h"
#include "IUpdatable.h"
#include "IPlayableWarp.h"

#include <vector>

namespace FR
{
	class AnimancerState;
	class AnimancerLayer;
	class AnimancerPlayable;
	class AnimationPlayable;

	class AnimancerNode
		: public IUpdatable, public IPlayableWarp, public ICopyable<AnimancerNode>
	{
	public:

#pragma region Playable
		virtual AnimationPlayable* Playable() override;

		virtual void CreatePlayable();

		virtual void CreatePlayable(AnimationPlayable*& pPlayable) = 0;

		virtual void DestroyPlayable();

		virtual void RecreatePlayable();

		virtual void CopyFrom(AnimancerNode* pCopyFrom);
#pragma endregion

#pragma region Graph
		virtual AnimancerPlayable* Root();

		virtual void SetRoot(AnimancerPlayable* pRoot);

		virtual AnimancerLayer* Layer();

		virtual IPlayableWarp* Parent() override;

		int Index();

		virtual void Update() override;
#pragma endregion

#pragma region Children
		virtual AnimancerState* GetChild();

		virtual void OnAddChild(AnimancerState* pState) {}

		virtual void OnRemoveChild(AnimancerState* pState) {}
#pragma endregion

#pragma region Weight
		virtual float Weight() override;

		virtual void SetWeight(float pWeight) override;

		void ApplyWeight();
#pragma endregion

#pragma region Fade
		void StartFade(float pTargetWeight);

		void StartFade(float pTargetWeight, float pFadeDuration);
		
		virtual void OnStartFade() = 0;

		virtual void Stop();
#pragma endregion

#pragma region Speed
		virtual float Speed() override;

		virtual void SetSpeed(float pSeed) override;
#pragma endregion

	protected:

#pragma region Graph
		void RequireUpdate();

		virtual void Update(bool& pNeedsMoreUpdates);
#pragma endregion

#pragma region Children
		void OnAddChild(std::vector<AnimancerState*>& pStates, AnimancerState* pState);
#pragma endregion

#pragma region Weight
		void SetWeightDirty();
#pragma endregion

	private:

#pragma region Graph
		void ConnectToGraph();

		void DisconnectFromGraph();

		void ApplyConnectedState(IPlayableWarp* pParent);
#pragma endregion

#pragma region Fade
		void UpdateFade(bool& pNeedsMoreUpdates);
#pragma endregion

#pragma region Speed
		float ParentEffectiveSpeed();
#pragma endregion

	public:
		float fadeSpeed{ 0.f };

		float targetWeight{ 0.f };

	protected:
		int mIndex{ 0 };

		AnimancerNode* mParent{ nullptr };

		AnimancerPlayable* mRoot{ nullptr };

		AnimationPlayable* mPlayable{ nullptr };

	private:
		float mSpeed{ 1.f };

		float mWeight{ 0.f };

		bool mIsWeightDirty{ false };

	};
}