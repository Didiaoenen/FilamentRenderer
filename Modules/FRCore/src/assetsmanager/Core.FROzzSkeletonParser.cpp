#include "Core.FROzzSkeletonParser.h"

#include <ozz/base/io/archive.h>
#include <ozz/animation/runtime/skeleton.h>

bool FR::FROzzSkeletonParser::LoadSkeleton(const std::string& pFilePath, ozz::animation::Skeleton& pSkeleton)
{
	ozz::io::File file(pFilePath.c_str(), "rb");
	if (!file.opened())
	{
		return false;
	}

	ozz::io::IArchive archive(&file);
	if (!archive.TestTag<ozz::animation::Skeleton>())
	{
		return false;
	}

	{
		archive >> pSkeleton;
	}

	return true;
}