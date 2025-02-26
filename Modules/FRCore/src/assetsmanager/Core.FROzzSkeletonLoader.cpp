#include "Core.FROzzSkeletonLoader.h"

#include "SkeletonRig.h"

#include <Tools.FRPathUtils.h>

#include <ozz/animation/runtime/skeleton.h>

FR::SkeletonRig* FR::FROzzSkeletonLoader::Create(const std::string& pFilePath)
{
	ozz::animation::Skeleton skeleton;
	if (__OZZ.LoadSkeleton(pFilePath, skeleton))
	{
		return new SkeletonRig(skeleton);
	}

	return nullptr;
}

void FR::FROzzSkeletonLoader::Reload(SkeletonRig& pSkeleton, const std::string& pFilePath)
{
}

void FR::FROzzSkeletonLoader::Destroy(SkeletonRig*& pSkeleton)
{
	delete pSkeleton; pSkeleton = nullptr;
}
