#include "Core.FRModelManager.h"

#include "Core.FRModel.h"
#include "Core.FRModelLoader.h"
#include "Core.FROzzModelLoader.h"

#include <Tools.FRPathUtils.h>

FR::FRModel* FR::FRModelManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	FR::EFileType fileType = FRPathUtils::GetFileType(pPath);

	FRModel* model = nullptr;
	switch (fileType)
	{
	case FR::EFileType::MODEL:
		model = FRModelLoader::Create(realPath);
		break;
	case FR::EFileType::OZZMODEL:
		model = FROzzModelLoader::Create(realPath);
		break;
	default:
		break;
	}

	if (model)
	{
		model->path = pPath;
	}
	return model;
}

void FR::FRModelManager::ReloadResource(FRModel* pResource, const std::string& pPath)
{
}

void FR::FRModelManager::DestroyResource(FRModel* pResource)
{
	FRModelLoader::Destroy(pResource);
}