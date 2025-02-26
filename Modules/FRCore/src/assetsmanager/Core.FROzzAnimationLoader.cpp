#include "Core.FROzzAnimationLoader.h"

#include "Animation.h"

#include <ozz/base/io/archive.h>
#include <ozz/animation/runtime/animation.h>

FR::Animation* FR::FROzzAnimationLoader::Create(const std::string& pFilePath)
{
	ozz::animation::Animation animation;
	LoadAnimation(pFilePath, animation);
	return new Animation(animation);
}

void FR::FROzzAnimationLoader::Reload(Animation& pAniamtin, const std::string& pFilePath)
{
}

void FR::FROzzAnimationLoader::Destroy(Animation*& pAniamtin)
{
	delete pAniamtin; pAniamtin = nullptr;
}

bool FR::FROzzAnimationLoader::LoadAnimation(const std::string& pFileName, ozz::animation::Animation& pAnimation)
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
		archive >> pAnimation;
	}

    return true;
}
