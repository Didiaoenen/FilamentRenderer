#pragma once

#include "AMotion.h"
#include <ozz/base/io/archive.h>
#include <ozz/base/memory/allocator.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>

namespace FR
{
	class AnimationMask;

	class Animation
		: public AMotion
	{
	public:
		Animation(ozz::animation::Animation* pAnimation);

		virtual bool InitData(SkeletonRig* pSkeletonRig) override;

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample(float pDeltaTime) override;
	
		float GetDurtion();

		void SetTimeRatio(float pTime);

		float GetTimeRatio();

		float GetPreviousTimeRatio();

		void Reset();

	public:
		~Animation();

	private:
		ozz::animation::Animation* mAnimation{ nullptr };

	public:
		bool play{ true };

		bool loop{ true };

		bool additive{ false };

		float weight{ 1.0f };

		float playbackSpeed{ 1.0f };

		AnimationMask* mask{ nullptr };

	private:
		float mTimeRatio{ 0.0f };

		float mPreviousTimeRatio{ 1.0f };

		ozz::animation::SamplingJob::Context mContext{};

	};
}

