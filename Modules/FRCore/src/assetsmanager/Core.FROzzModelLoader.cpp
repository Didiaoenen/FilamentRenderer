#include "Core.FROzzModelLoader.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"
#include "SkeletonRig.h"

#include <StringExtension.h>
#include <Tools.FRPathUtils.h>

#include <ozz/animation/runtime/skeleton.h>

FR::FRModel* FR::FROzzModelLoader::Create(const std::string& pFilePath)
{
	FRModelData dataTree;
	std::vector<std::string> materialNames;

	if (__OZZ.LoadMesh(pFilePath, dataTree, materialNames))
	{
		FRModel* result = new FRModel();
		result->mMaterialNames = materialNames;

		for (auto mesh : dataTree.meshs)
		{
			result->SetMesh(mesh);
		}

		return result;
	}

	return nullptr;
}

void FR::FROzzModelLoader::Reload(FRModel& pModel, const std::string& pFilePath)
{
}

void FR::FROzzModelLoader::Destroy(FRModel*& pModel)
{
	delete pModel; pModel = nullptr;
}
