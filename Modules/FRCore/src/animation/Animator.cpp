#include "Animator.h"
#include "BlendTree.h"
#include "SkeletonRig.h"

#include "Animation.h"
#include "AnimancerPlayable.h"

#include <ozz/animation/runtime/local_to_model_job.h>

FR::Animator::Animator()
{
}

bool FR::Animator::Update(float pDeltaTime)
{
	return true;
}

FR::SkeletonRig* FR::Animator::GetSkeletonRig() const
{
	return mSkeleton;
}

void FR::Animator::SetSkeletonRig(SkeletonRig* pSkeletonRig)
{
	mSkeleton = pSkeletonRig;

	mJointModelMats.resize(pSkeletonRig->GetNumJoints());
	mJointWorldMats.resize(pSkeletonRig->GetNumJoints());

	for (uint32_t i = 0; i < mSkeleton->GetNumJoints(); i++)
	{
		mJointModelMats[i] = ozz::math::Float4x4::identity();
		mJointWorldMats[i] = ozz::math::Float4x4::identity();
	}
}

void FR::Animator::Play(AMotion* pMotion, float pTime)
{
}

void FR::Animator::ComputePose(const ozz::math::Float4x4& pRootTrans)
{
	for (uint32_t i = 0; i < mSkeleton->GetNumJoints(); i++)
	{
		mJointWorldMats[i] = pRootTrans * mJointModelMats[i];
	}
}

void FR::Animator::ComputeBindPose(const ozz::math::Float4x4& pRootTrans)
{
	ozz::animation::LocalToModelJob ltmJob;
	ltmJob.skeleton = &mSkeleton->GetSkeleton();
	ltmJob.input = mSkeleton->GetJointsRestPoses();
	ltmJob.output = make_span(mJointModelMats);

	if (ltmJob.Run())
	{
		ComputePose(pRootTrans);
	}
}

void FR::Animator::ComputeJointScales(const ozz::math::Float4x4& pRootTrans)
{
}

ozz::math::Float4x4 FR::Animator::GetJointWorldMatNoScale(uint32_t index) const
{
	return mJointWorldMats[index + mSkeleton->rootIndex];
}

bool FR::Animator::Sample(const ozz::vector<ozz::math::SoaTransform>& pInputTrans)
{
	if (mSkeleton)
	{
		ozz::animation::LocalToModelJob ltmJob;
		ltmJob.input = make_span(pInputTrans);
		ltmJob.output = make_span(mJointModelMats);
		ltmJob.skeleton = &mSkeleton->GetSkeleton();

		if (!ltmJob.Run())
		{
			return false;
		}

		ComputePose(mRootTrans);
	}

	return true;
}

bool FR::Animator::AnimationIK()
{
	return false;
}

FR::Animator::~Animator()
{
}