#include "Core.FRShaderManager.h"

#include "Core.FRShader.h"
#include "Core.FRShaderLoader.h"

#include <Tools.FRPathUtils.h>

FR::FRShader* FR::FRShaderManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (auto shader = FRShaderLoader::Create(realPath))
	{
		shader->path = pPath;
		return shader;
	}
	return nullptr;
}

void FR::FRShaderManager::ReloadResource(FRShader* pResource, const std::string& pPath)
{
}

void FR::FRShaderManager::DestroyResource(FRShader* pResource)
{
	FRShaderLoader::Destroy(pResource);
}