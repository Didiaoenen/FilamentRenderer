#include "Core.FRMaterialManager.h"

#include "Core.FRMaterial.h"
#include "Core.FRMaterialLoader.h"

#include <Tools.FRPathUtils.h>

FR::FRMaterial* FR::FRMaterialManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (FRMaterial* material = FRMaterialLoader::Create(realPath))
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(material) + offsetof(FRMaterial, path)) = pPath;
		return material;
	}
	return nullptr;
}

void FR::FRMaterialManager::DestroyResource(FRMaterial* pResource)
{
}

void FR::FRMaterialManager::ReloadResource(FRMaterial* pResource, const std::string& pPath)
{
}
