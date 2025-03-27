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

		SkeletonRig* GetSkeletonRig() const;

		void SetSkeletonRig(SkeletonRig* pSkeletonRig);

		void Play(AMotion* pMotion, float pTime = 0.0f);

		void ComputePose(const ozz::math::Float4x4& pRootTrans);

		void ComputeBindPose(const ozz::math::Float4x4& pRootTrans);

		void ComputeJointScales(const ozz::math::Float4x4& pRootTrans);

		ozz::math::Float4x4 GetJointWorldMatNoScale(uint32_t index) const;

		bool Sample(const ozz::vector<ozz::math::SoaTransform>& pInputTrans);

		bool AnimationIK();

	public:
		virtual ~Animator();

	private:
		SkeletonRig* mSkeleton{ nullptr };

		ozz::math::Float4x4 mRootTrans{ ozz::math::Float4x4::identity() };

		ozz::vector<ozz::math::Float4x4> mJointModelMats;

		ozz::vector<ozz::math::Float4x4> mJointWorldMats;

		ozz::span<ozz::math::Float3> mJointScales{};
		
		ozz::math::Float4 mJointColor{};

		ozz::math::Float4 mBoneColor{};

	};
}

