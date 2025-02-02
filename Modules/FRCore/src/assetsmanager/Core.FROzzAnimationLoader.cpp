#include "Core.FROzzAnimationLoader.h"

#include "Animation.h"

#include <ozz/base/io/archive.h>
#include <ozz/animation/runtime/animation.h>

FR::Animation* FR::FROzzAnimationLoader::Create(const std::string& pFilePath)
{
	auto animation = new ozz::animation::Animation();
	LoadAnimation(pFilePath, animation);
	return new Animation(animation);
}

bool FR::FROzzAnimationLoader::LoadAnimation(const std::string& pFileName, ozz::animation::Animation* pAnimation)
{
	ozz::io::File file(pFileName.c_str(), "rb");
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
		archive >> *pAnimation;
	}

    return true;
}
