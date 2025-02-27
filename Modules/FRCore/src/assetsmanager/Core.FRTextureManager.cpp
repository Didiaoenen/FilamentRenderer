#include "Core.FRTextureManager.h"

#include "Core.FRTexture2D.h"
#include "Core.FRTextureLoader.h"

#include <Tools.FRPathUtils.h>

FR::FRTexture2D* FR::FRTextureManager::CreateResource(const std::string& pPath)
{
    std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (FRTexture2D* texture = FRTextureLoader::Create(realPath,
		FRTextureSamplerWarp::EMinFilter::LINEAR_MIPMAP_LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR, false))
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(texture) + offsetof(FRTexture2D, path)) = pPath;
		return texture;
	}
	return nullptr;
}

void FR::FRTextureManager::ReloadResource(FRTexture2D* pResource, const std::string& pPath)
{
}

void FR::FRTextureManager::DestroyResource(FRTexture2D* pResource)
{
	FRTextureLoader::Destroy(pResource);
}
