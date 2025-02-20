#include "Animator.h"
#include "BlendTree.h"
#include "SkeletonRig.h"

#include <ozz/animation/runtime/local_to_model_job.h>

FR::Animator::Animator()
{
}

bool FR::Animator::Update(float pDeltaTime)
{
	if (mMotion)
	{
		mMotion->Update(pDeltaTime);

		if (!mMotion->Sample(pDeltaTime))
		{
			return false;
		}

		auto localTrans = mMotion->GetLocalTrans();
		ozz::animation::LocalToModelJob ltmJob;
		ltmJob.skeleton = &mSkeletonRig->GetSkeleton();
		ltmJob.input = make_span(localTrans);
		ltmJob.output = make_span(mJointModelMats);

		if (!ltmJob.Run())
		{
			return false;
		}

		ComputePose(mRootTrans);
	}

	return true;
}

void FR::Animator::SetSkeletonRig(SkeletonRig* pSkeletonRig)
{
	mSkeletonRig = pSkeletonRig;

	mJointModelMats.resize(pSkeletonRig->GetNumJoints());
	mJointWorldMats.resize(pSkeletonRig->GetNumJoints());

	for (uint32_t i = 0; i < mSkeletonRig->GetNumJoints(); i++)
	{
		mJointModelMats[i] = ozz::math::Float4x4::identity();
		mJointWorldMats[i] = ozz::math::Float4x4::identity();
	}
}

void FR::Animator::Play(AMotion* pMotion, float pTime)
{
	mMotion = pMotion;
	mMotion->InitData(mSkeletonRig);

	ComputeBindPose(mRootTrans);
}

void FR::Animator::ComputePose(const ozz::math::Float4x4& pRootTrans)
{
	for (uint32_t i = 0; i < mSkeletonRig->GetNumJoints(); i++)
	{
		mJointWorldMats[i] = pRootTrans * mJointModelMats[i];
	}
}

void FR::Animator::ComputeBindPose(const ozz::math::Float4x4& pRootTrans)
{
	ozz::animation::LocalToModelJob ltmJob;
	ltmJob.skeleton = &mSkeletonRig->GetSkeleton();
	ltmJob.input = mSkeletonRig->GetJointsRestPoses();
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
	return mJointWorldMats[index + mSkeletonRig->rootIndex];
}

bool FR::Animator::AnimationIK()
{
	return false;
}

FR::Animator::~Animator()
{
}