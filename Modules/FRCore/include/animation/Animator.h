#pragma once

#include "COre.FRObject.h"
#include <ozz/base/span.h>
#include <ozz/base/maths/vec_float.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/base/containers/vector.h>

namespace FR
{
	class AMotion;
	class SkeletonRig;

	class Animator
		: public FRObject
	{
	public:
		Animator();

		bool Update(float pDeltaTime);

		void SetSkeletonRig(SkeletonRig* pSkeletonRig);

		void Play(AMotion* pMotion, float pTime = 0.0f);

		void ComputePose(const ozz::math::Float4x4& pRootTrans);

		void ComputeBindPose(const ozz::math::Float4x4& pRootTrans);

		void ComputeJointScales(const ozz::math::Float4x4& pRootTrans);

		ozz::math::Float4x4 GetJointWorldMatNoScale(uint32_t index) const;

		bool AnimationIK();

	public:
		virtual ~Animator();

	private:
		AMotion* mMotion{ nullptr };

		SkeletonRig* mSkeletonRig{ nullptr };

		ozz::math::Float4x4 mRootTrans{ ozz::math::Float4x4::identity() };

		ozz::vector<ozz::math::Float4x4> mJointModelMats;

		ozz::vector<ozz::math::Float4x4> mJointWorldMats;

		ozz::math::Float4 mJointColor{};

		ozz::math::Float4 mBoneColor{};

		ozz::span<ozz::math::Float3> mJointScales{};

	};
}

