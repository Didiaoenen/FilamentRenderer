#include "Core.FRModelLoader.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"

#include <Tools.FRPathUtils.h>

namespace FR
{
	FRAssimpParser FRModelLoader::__ASSIMP;
}

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
			result->AddMesh(mesh);
			mesh->CreateRenderer(result);
			mesh->SetParentRender(result);
		}

		return result;
	}
	return nullptr;
}

void FR::FRModelLoader::Reload(FRModel& pModel, const std::string& pFilePath)
{
}

bool FR::FRModelLoader::Destroy(FRModel*& pModelInstance)
{
    return false;
}