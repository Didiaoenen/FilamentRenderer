#pragma once

#include "AnimancerNode.h"

#include <any>

namespace FR
{
    class AnimationClip;
    class AnimancerLayer;
    class AnimancerPlayable;

    class AnimancerState
        : public AnimancerNode, ICopyable<AnimancerState>
    {
    public:
        using AnimancerNode::Update;

        AnimancerState(AnimationClip* pClip = nullptr);

        void SetRoot(AnimancerPlayable* pRoot);

		virtual IPlayableWarp* Parent() override;

        void SetParent(AnimancerNode* pParent, int pIndex);

		void SetParentInternal(AnimancerNode* pParent, int pIndex = -1);

		virtual AnimancerLayer* Layer() override;

		std::any Key();

		void SetKey(std::any pAny);

		AnimationClip* Clip();

		void SetClip(AnimationClip* pClip);

		bool IsPlaying();

		void SetPlaying(bool pPlay);

		void OnSetIsPlaying() {}

		virtual void CreatePlayable() override;

		virtual void CreatePlayable(AnimationPlayable*& pPlayable) override;

		void Play();

		void Stop();

		virtual void OnStartFade() override;

		AnimancerState* Clone();

		AnimancerState* Clone(AnimancerPlayable* pRoot);

        virtual void CopyFrom(AnimancerState* pState);

    protected:
		virtual void Update(bool& pNeedsMoreUpdates) override;

        void SetNewCloneRoot(AnimancerPlayable* pRoot);

	public:
		virtual ~AnimancerState();

    private:
        std::any mKey;

		bool mIsPlaying{ false };

        bool mIsPlayingDirty{ true };

		AnimationClip* mClip{ nullptr };

    };
}