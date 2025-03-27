#pragma once

#include "IPlayableWarp.h"
#include "AnimancerPlayable.LayerVec.h"
#include "AnimancerPlayable.StateMap.h"

#include <any>
#include <map>
#include <vector>

namespace FR
{
	class IUpdatable;

    class PlayableGraph;
    class AnimationClip;
    class AnimancerLayer;
    class AnimancerState;
    class AnimationBasePlayable;
    class AnimationPlayableOutput;

	class FRCompAnimator;

    class AnimancerPlayable
        : public IPlayableWarp
    {
        friend class LayerVec;
        friend class StateMap;

    public:
        AnimancerPlayable();

		PlayableGraph* Graph();

		virtual AnimationPlayable* Playable() override;

		virtual IPlayableWarp* Parent() override;

		virtual float Weight() override;

		virtual void SetWeight(float pWeight) override;

        virtual float Speed() override;

		virtual void SetSpeed(float pSpeed) override;

		void CreateOutput(FRCompAnimator* pAnimator);

		std::any GetKey(AnimationClip* pClip);

		AnimancerState* Play(AnimationClip* pClip);

		AnimancerState* Play(AnimancerState* pState);

		AnimancerState* Play(AnimationClip* pClip, float pFadeDuration);

		AnimancerState* Play(AnimancerState* pState, float pFadeDuration);

        void Stop();

        bool IsPlaying();

        bool IsPlayingClip(AnimationClip* pClip);

        void RequirePreUpdate(IUpdatable* pUpdateble);

        void RequirePostUpdate(IUpdatable* pUpdateble);

		void CancelPreUpdate(IUpdatable* pUpdateble);

		void CancelPostUpdate(IUpdatable* pUpdateble);

		void PrepareFrame(float pDeltaTime);

        void SetGraphPlaying(bool pIsPlaying);

    private:
        AnimancerLayer* GetLocalLayer(AnimancerState* pState);

		void CancelUpdate(std::vector<IUpdatable*>& pUpdateables, IUpdatable* pUpdateable);

        void UpdateAll(std::vector<IUpdatable*> pUpdateables, float pDeltaTime);

    public:
        virtual ~AnimancerPlayable();

    public:
		inline static float deltaTime{ 0.f };

        inline static float defaultFadeDuration{ 0.25f };

		inline static AnimancerPlayable* current{ nullptr };

    private:
        float mSpeed{ 1.f };

		float mWeight{ 1.f };

        int mUpdateableCount{ 0 };

        bool mIsGraphPlaying{ true };

		std::vector<IUpdatable*> mPreUpdatables;

		std::vector<IUpdatable*> mCurrUpdatables;

		PlayableGraph* mGraph{ nullptr };

        AnimationPlayable* mPlayable{ nullptr };

		AnimationBasePlayable* mRootPlayable{ nullptr };

        AnimationPlayableOutput* mOutput{ nullptr };

    public:
		LayerVec layers;

		StateMap states;

    };
}