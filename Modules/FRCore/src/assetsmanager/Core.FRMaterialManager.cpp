#include "Core.FRMaterialManager.h"

#include "Core.FRMaterial.h"
#include "Core.FRMaterialLoader.h"

#include <Tools.FRPathUtils.h>

FR::FRMaterial* FR::FRMaterialManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (FRMaterial* material = FRMaterialLoader::Create(realPath))
	{
		material->path = pPath;
		return material;
	}
	return nullptr;
}

void FR::FRMaterialManager::ReloadResource(FRMaterial* pResource, const std::string& pPath)
{

}

void FR::FRMaterialManager::DestroyResource(FRMaterial* pResource)
{
	FRMaterialLoader::Destroy(pResource);
}