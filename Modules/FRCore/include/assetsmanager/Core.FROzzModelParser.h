#pragma once

#include <vector>
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
	struct FRModelData;

	class FROzzModelParser
	{
	public:
		bool LoadMesh(const std::string& pFilePath, FRModelData& pOutData, std::vector<std::string>& pMaterials);

		bool LoadSkeleton(const std::string& pFilePath, ozz::animation::Skeleton& pSkeleton);

	};
}

