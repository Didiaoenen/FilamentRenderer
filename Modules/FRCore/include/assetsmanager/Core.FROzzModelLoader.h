#pragma once

#include "Core.FROzzModelParser.h"

namespace FR
{
	class FRModel;
	class SkeletonRig;

	class FROzzModelLoader
	{
	public:
		static FRModel* Create(const std::string& pFilePath);

		static void Reload(FRModel& pModel, const std::string& pFilePath);

		static void Destroy(FRModel*& pModel);

	private:
		inline static FROzzModelParser __OZZ;

	};
}

