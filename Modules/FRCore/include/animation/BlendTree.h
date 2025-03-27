#pragma once

#include "AMotion.h"
#include <ozz/base/containers/vector.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/animation/runtime/blending_job.h>

namespace FR
{
	class Animation;
	class AnimationMask;

	class BlendTree
		: public AMotion
	{
	public:

		enum class EBlendType
		{
			EQUAL,
			CROSS_DISSOLVE,
			CROSS_DISSOLVE_SYNC,
			MANUAL
		};

		BlendTree();

		void AddMotion(AMotion* pMotion);

		virtual bool InitData(SkeletonRig* pSkeletonRig) override;

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample(float pDeltaTime) override;

		virtual void SetTimeRatio(float pTimeRatio);

		virtual float GetTimeRatio() override;

		virtual float GetDuration() override;

	private:
		void UpdateBlendParameters();

		bool Blend();

	public:
		~BlendTree() = default;

	public:
		float threshold{ 0.1f };

		float blendRatio{ 0.5f };
		
		bool autoSetBlendParams{ true };

		EBlendType blendType{ EBlendType::MANUAL };

	private:
		ozz::vector<AMotion*> mMotions;

		ozz::vector<ozz::animation::BlendingJob::Layer> mLayers;

		ozz::vector<ozz::animation::BlendingJob::Layer> mAdditiveLayers;

		uint32_t mNumAdditiveClips{ 0 };

		uint32_t mLongestClipIndex{ 0 };

		float mDuration{ 0.0f };

	};
}

