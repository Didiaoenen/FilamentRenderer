#pragma once

#include <string>

namespace ozz
{
	namespace animation
	{
		class Skeleton;
	}
}

namespace FR
{
	class FROzzSkeletonParser
	{
	public:
		bool LoadSkeleton(const std::string& pFilePath, ozz::animation::Skeleton& pSkeleton);

	};
}
