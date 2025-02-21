#include "Core.FRModelLoader.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"

#include <Tools.FRPathUtils.h>

FR::FRModel* FR::FRModelLoader::Create(const std::string& pFilepath)
{
	FRModelData dataTree;
	std::vector<std::string> materialNames;
	if (__ASSIMP.LoadModel(pFilepath, dataTree, materialNames))
	{
		FRModel* result = new FRModel();
		result->mMaterialNames = materialNames;

		for (auto mesh : dataTree.meshs)
		{
			result->AttachmentMesh(mesh);
		}

		return result;
	}

	return nullptr;
}

void FR::FRModelLoader::Reload(FRModel& pModel, const std::string& pFilePath)
{
}

void FR::FRModelLoader::Destroy(FRModel*& pModel)
{
	delete pModel; pModel = nullptr;
}
