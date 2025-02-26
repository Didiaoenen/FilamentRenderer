#pragma once

#include "Core.FROzzSkeletonParser.h"

namespace FR
{
	class SkeletonRig;

	class FROzzSkeletonLoader
	{
	public:
		static SkeletonRig* Create(const std::string& pFilePath);

		static void Reload(SkeletonRig& pSkeleton, const std::string& pFilePath);

		static void Destroy(SkeletonRig*& pSkeleton);

	private:
		inline static FROzzSkeletonParser __OZZ;

	};
}

