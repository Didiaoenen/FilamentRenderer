#include "Core.FROzzAnimationManager.h"
#include "Core.FROzzAnimationLoader.h"

#include "Animation.h"

#include <Tools.FRPathUtils.h>

FR::Animation* FR::FROzzAnimationManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (auto animation = FROzzAnimationLoader::Create(realPath))
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(animation) + offsetof(Animation, path)) = pPath;
		return animation;
	}
	return nullptr;
}

void FR::FROzzAnimationManager::ReloadResource(Animation* pResource, const std::string& pPath)
{
}

void FR::FROzzAnimationManager::DestroyResource(Animation* pResource)
{
	FROzzAnimationLoader::Destroy(pResource);
}