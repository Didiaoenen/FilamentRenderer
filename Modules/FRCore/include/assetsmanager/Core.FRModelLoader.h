#pragma once

#include "Core.FRAssimpParser.h"

namespace FR
{
	class FRModel;

	class FRModelLoader
	{
	public:
		static FRModel* Create(const std::string& pFilepath);

		static void Reload(FRModel& pModel, const std::string& pFilePath);

		static void Destroy(FRModel*& pModel);

	private:
		inline static FRAssimpParser __ASSIMP;

	};
}

