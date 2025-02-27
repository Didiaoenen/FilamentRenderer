#pragma once

#include "AMotion.h"
#include <ozz/base/io/archive.h>
#include <ozz/base/memory/allocator.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>

namespace FR
{
	class AnimationClip;
	class AnimationMask;

	class Animation
		: public AMotion
	{
	public:
		Animation(AnimationClip* pClip);

		virtual bool InitData(SkeletonRig* pSkeletonRig) override;

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample(float pDeltaTime) override;
	
		void SetTimeRatio(float pTime);
	
		float GetDurtion();

		float GetTimeRatio();

		float GetPreviousTimeRatio();

		void Reset();

	public:
		virtual ~Animation();

	public:
		bool play{ true };

		bool loop{ true };

		bool additive{ false };

		float weight{ 1.0f };

		float playbackSpeed{ 1.0f };

		AnimationClip* clip{ nullptr };

		AnimationMask* mask{ nullptr };

	private:
		float mTimeRatio{ 0.0f };

		float mPreviousTimeRatio{ 1.0f };

		ozz::animation::SamplingJob::Context mContext;

	};
}

