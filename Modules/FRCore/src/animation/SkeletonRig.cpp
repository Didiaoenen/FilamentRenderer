#include "SkeletonRig.h"

FR::SkeletonRig::SkeletonRig(ozz::animation::Skeleton& pSkeleton)
	: mSkeleton(std::move(pSkeleton))
{
	mNumJoints = mSkeleton.num_joints();
	mNumSoaJoints = mSkeleton.num_soa_joints();

	rootIndex = std::max(FindJoint("Root"), 0);
}

ozz::animation::Skeleton& FR::SkeletonRig::GetSkeleton()
{
	return mSkeleton;
}

uint32_t FR::SkeletonRig::GetNumJoints()
{
	return mNumJoints;
}

uint32_t FR::SkeletonRig::GetNumSoaJoints()
{
	return mNumSoaJoints;
}

ozz::span<const ozz::math::SoaTransform> FR::SkeletonRig::GetJointsRestPoses()
{
	return mSkeleton.joint_rest_poses();
}

void FR::SkeletonRig::Pose(const ozz::math::Float4x4& pRootTrans)
{
}

int32_t FR::SkeletonRig::FindJoint(const std::string& pJointName)
{
	for (uint32_t i = 0; i < mNumJoints; i++)
	{
		if (strcmp(mSkeleton.joint_names()[i], pJointName.c_str()) == 0)
		{
			return i;
		}
	}
	return -1;
}

FR::SkeletonRig::~SkeletonRig()
{
}