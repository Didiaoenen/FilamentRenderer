#pragma once

#include "APlayable.h"
#include <ozz/base/containers/vector.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/animation/runtime/blending_job.h>

namespace FR
{
	class SkeletonRig;
	class AnimationMask;
	class APlayableParent;
	class AnimationPlayableOutput;

	class AnimationPlayable
		: public APlayable
	{
	public:
		AnimationPlayable() = default;

		virtual bool InitData() = 0;

		virtual void SetTimeRatio(float pTime) = 0;

		virtual void SetSpeed(float pSpeed) = 0;

		virtual float GetDuration() = 0;

		AnimationPlayable* GetRootPlayable();

		AnimationPlayableOutput* GetOutput();

        void SetOutput(AnimationPlayableOutput* pOutput);

		const ozz::vector<ozz::math::SoaTransform>& GetLocalTrans();

	public:
		bool play{ true };

		bool loop{ true };

		float weight{ 1.f };

		float threshold{ 0.1f };

		AnimationMask* mask{ nullptr };

		APlayableParent* parent{ nullptr };

		bool isInit{ false };

	protected:
		float mSpeed{ 1.f };
		
		float mTimeRatio{ 0.f };

		SkeletonRig* mSkeleton{ nullptr };

		ozz::vector<ozz::math::SoaTransform> mLocalTrans;

		ozz::vector<ozz::animation::BlendingJob::Layer> mLayers;

	};
}