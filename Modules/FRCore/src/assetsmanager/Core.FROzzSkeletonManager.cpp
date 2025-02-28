#include "Core.FROzzSkeletonManager.h"
#include "Core.FROzzSkeletonLoader.h"
#include "SkeletonRig.h"

#include <Tools.FRPathUtils.h>

FR::SkeletonRig* FR::FROzzSkeletonManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (auto skeleton = FROzzSkeletonLoader::Create(realPath))
	{
		skeleton->path = pPath;
		return skeleton;
	}
	return nullptr;
}

void FR::FROzzSkeletonManager::ReloadResource(SkeletonRig* pResource, const std::string& pPath)
{
}

void FR::FROzzSkeletonManager::DestroyResource(SkeletonRig* pResource)
{
	FROzzSkeletonLoader::Destroy(pResource);
}
