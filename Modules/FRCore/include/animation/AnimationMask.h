#pragma once

#include "COre.FRObject.h"
#include <ozz/base/span.h>
#include <ozz/base/maths/vec_float.h>
#include <ozz/base/maths/simd_math.h>
#include <ozz/base/containers/vector.h>

namespace FR
{
	class SkeletonRig;

	class AnimationMask
		: public FRObject
	{
	public:
		AnimationMask(SkeletonRig* pSkeletonRig);

		void EnableAllJoints();

		void DisableAllJoints();

		void SetAllChildrenOf(int32_t pJointIndex, float pValue);

		ozz::vector<ozz::math::SimdFloat4>& GetJointWeights();

	public:
		~AnimationMask() = default;

	private:
		SkeletonRig* mSkeletonRig{ nullptr };

		ozz::vector<ozz::math::SimdFloat4> mJointWeights;
	};
}

