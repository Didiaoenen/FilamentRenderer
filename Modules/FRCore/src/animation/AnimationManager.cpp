#include "AnimationManager.h"
#include "Animation.h"

#include "Core.FROzzAnimationLoader.h"

#include <Tools.FRPathUtils.h>

FR::Animation* FR::AnimationManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (auto animation = FROzzAnimationLoader::Create(realPath))
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(animation) + offsetof(Animation, path)) = pPath;
		return animation;
	}
	return nullptr;
}

void FR::AnimationManager::ReloadResource(Animation* pResource, const std::string& pPath)
{
}

void FR::AnimationManager::DestroyResource(Animation* pResource)
{
}