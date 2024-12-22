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
		FROzzModelParser() = default;

		bool LoadMesh(const std::string& pFileName, FRModelData& pOutData, std::vector<std::string>& pMaterials);

		bool LoadSkeleton(const std::string& pFileName, ozz::animation::Skeleton* pSkeleton);

	public:
		~FROzzModelParser() = default;

	};
}

