#include "AnimationMask.h"
#include "SkeletonRig.h"

FR::AnimationMask::AnimationMask(SkeletonRig* pSkeletonRig)
	: mSkeletonRig(pSkeletonRig)
{
	EnableAllJoints();
}

void FR::AnimationMask::EnableAllJoints()
{
	mJointWeights.resize(mSkeletonRig->GetNumSoaJoints(), ozz::math::simd_float4::one());
}

void FR::AnimationMask::DisableAllJoints()
{
	mJointWeights.resize(mSkeletonRig->GetNumSoaJoints(), ozz::math::simd_float4::zero());
}

void FR::AnimationMask::SetAllChildrenOf(int32_t pJointIndex, float pValue)
{
	auto functor = [this, pValue](int32_t joint, int16_t jointParent)
		{
			ozz::math::SimdFloat4& weight = mJointWeights[joint / 4];
			weight = ozz::math::SetI(weight, ozz::math::simd_float4::Load1(pValue), joint % 4);
		};

	ozz::animation::IterateJointsDF(*mSkeletonRig->GetSkeleton(), functor, pJointIndex);
}

ozz::vector<ozz::math::SimdFloat4>& FR::AnimationMask::GetJointWeights()
{
	return mJointWeights;
}
