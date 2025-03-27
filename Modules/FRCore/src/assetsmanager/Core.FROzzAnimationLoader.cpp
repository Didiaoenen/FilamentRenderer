#include "Core.FROzzAnimationLoader.h"

#include "AnimationClip.h"

#include <ozz/base/io/archive.h>
#include <ozz/animation/runtime/animation.h>

FR::AnimationClip* FR::FROzzAnimationLoader::Create(const std::string& pFilePath)
{
	ozz::animation::Animation animation;
	LoadAnimation(pFilePath, animation);
	return new AnimationClip(std::move(animation));
}

void FR::FROzzAnimationLoader::Reload(AnimationClip& pAniamtin, const std::string& pFilePath)
{
}

void FR::FROzzAnimationLoader::Destroy(AnimationClip*& pAniamtinClip)
{
	delete pAniamtinClip; pAniamtinClip = nullptr;
}

bool FR::FROzzAnimationLoader::LoadAnimation(const std::string& pFilePath, ozz::animation::Animation& pAnimation)
{
	ozz::io::File file(pFilePath.c_str(), "rb");
	if (!file.opened())
	{
		return false;
	}

	ozz::io::IArchive archive(&file);
	if (!archive.TestTag<ozz::animation::Animation>())
	{
		return false;
	}

	{
		archive >> pAnimation;
	}

    return true;
}
