#include "AnimationManager.h"
#include "Animation.h"

#include "Core.FROzzAnimationLoader.h"

#include <Tools.FRPathUtils.h>

FR::Animation* FR::AnimationManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	auto animation = FROzzAnimationLoader::Create(realPath);
	if (animation)
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(animation) + offsetof(Animation, path)) = pPath;
	}
	return animation;
}

void FR::AnimationManager::DestroyResource(Animation* pResource)
{
}

void FR::AnimationManager::ReloadResource(Animation* pResource, const std::string& pPath)
{
}
