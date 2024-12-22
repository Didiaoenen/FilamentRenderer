#pragma once

#include "Core.FRObject.h"
#include <ozz/base/span.h>
#include <ozz/base/io/archive.h>
#include <ozz/base/maths/simd_math.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/skeleton_utils.h>

namespace FR
{
	class SkeletonRig
		: public FRObject
	{
	public:
		SkeletonRig(ozz::animation::Skeleton* pSkeleton);

		uint32_t GetNumJoints();

		uint32_t GetNumSoaJoints();

		ozz::span<const ozz::math::SoaTransform> GetJointsRestPoses();

		void Pose(const ozz::math::Float4x4& pRootTrans);

		int32_t FindJoint(const std::string& pJointName);

		ozz::animation::Skeleton* GetSkeleton();

	public:
		~SkeletonRig();

	public:
		std::string path;
		uint32_t rootIndex{ 0 };

	private:
		ozz::animation::Skeleton* mSkeleton{ nullptr };

		uint32_t mNumSoaJoints{ 0 };

		uint32_t mNumJoints{ 0 };

	};
}

