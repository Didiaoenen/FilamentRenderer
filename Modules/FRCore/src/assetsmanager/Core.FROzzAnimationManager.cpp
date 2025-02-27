#include "Core.FROzzAnimationManager.h"
#include "Core.FROzzAnimationLoader.h"

#include "AnimationClip.h"

#include <Tools.FRPathUtils.h>

FR::AnimationClip* FR::FROzzAnimationManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (auto animation = FROzzAnimationLoader::Create(realPath))
	{
		animation->path = pPath;
		return animation;
	}
	return nullptr;
}

void FR::FROzzAnimationManager::ReloadResource(AnimationClip* pResource, const std::string& pPath)
{
}

void FR::FROzzAnimationManager::DestroyResource(AnimationClip* pResource)
{
	FROzzAnimationLoader::Destroy(pResource);
}