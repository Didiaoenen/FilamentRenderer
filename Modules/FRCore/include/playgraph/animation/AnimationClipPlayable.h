#pragma once

#include "AnimationPlayable.h"
#include <ozz/base/io/archive.h>
#include <ozz/base/memory/allocator.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>

namespace FR
{
	class PlayableGraph;
	class AnimationClip;

	class AnimationClipPlayable
		: public AnimationPlayable
	{
	public:
		AnimationClipPlayable(PlayableGraph* pGraph, AnimationClip* pClip);

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample() override;

		virtual bool InitData() override;

		virtual void SetTimeRatio(float pTime) override;

		virtual void SetSpeed(float pSpeed) override;

		virtual float GetDuration() override;

		void Reset();

	public:
		~AnimationClipPlayable() = default;

	private:
		AnimationClip* mClip{ nullptr };

		ozz::animation::SamplingJob::Context mContext;

	};
}