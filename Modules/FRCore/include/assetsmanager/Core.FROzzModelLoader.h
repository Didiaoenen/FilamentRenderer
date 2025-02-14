#pragma once

#include <string>
#include "Core.FROzzModelParser.h"

namespace FR
{
	class FRModel;
	class SkeletonRig;

	class FROzzModelLoader
	{
	public:
		static FRModel* Create(const std::string& pFilepath);

		static void Reload(FRModel& pModel, const std::string& pFilePath);

		static bool Destroy(FRModel*& pModelInstance);

	private:
		inline static FROzzModelParser __OZZ;

	};
}

