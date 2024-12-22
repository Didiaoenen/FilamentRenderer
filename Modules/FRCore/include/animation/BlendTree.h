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
		const uint32_t MAX_NUM_CLIPS = 0xF;

	public:

		enum class EBlendType
		{
			EQUAL,
			CROSS_DISSOLVE,
			CROSS_DISSOLVE_SYNC,
			MANUAL
		};

		BlendTree(ozz::vector<Animation*> pClips);

		virtual bool InitData(SkeletonRig* pSkeletonRig) override;

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample(float pDeltaTime) override;

		void SetTimeRatio(float pTimeRatio);

		float GetDuration();

	private:
		void UpdateBlendParameters();

		bool Blend();

	public:
		~BlendTree() = default;

	public:
		float threshold{ 0.1f };

		float blendRatio{ 0.5f };
		
		float playbackSpeed{ 1.0f };

		bool autoSetBlendParams{ true };

		EBlendType blendType{ EBlendType::EQUAL };

	private:
		ozz::vector<Animation*> mClips;

		ozz::vector<ozz::animation::BlendingJob::Layer> mLayers;

		ozz::vector<ozz::animation::BlendingJob::Layer> mAdditiveLayers;

		uint32_t mNumAdditiveClips{ 0 };

		uint32_t mLongestClipIndex{ 0 };

		float mTimeRatio{ 0.0f };

		float mDuration{ 0.0f };

	};
}

