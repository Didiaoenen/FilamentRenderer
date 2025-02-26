#pragma once

#include <string>
#include <vector>

namespace FR
{
	struct FRModelData;

	class FROzzModelParser
	{
	public:
		bool LoadMesh(const std::string& pFilePath, FRModelData& pOutData, std::vector<std::string>& pMaterials);

	};
}
