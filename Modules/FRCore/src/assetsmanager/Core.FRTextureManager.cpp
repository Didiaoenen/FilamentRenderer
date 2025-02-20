#include "Core.FRTextureManager.h"

#include "Core.FRTexture.h"
#include "Core.FRTextureLoader.h"

#include <Tools.FRPathUtils.h>

FR::FRTexture* FR::FRTextureManager::CreateResource(const std::string& pPath)
{
    std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (FRTexture* texture = FRTextureLoader::Create(realPath,
		FRTextureSamplerWarp::EMinFilter::LINEAR_MIPMAP_LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR, false))
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(texture) + offsetof(FRTexture, path)) = pPath;
		return texture;
	}
	return nullptr;
}

void FR::FRTextureManager::ReloadResource(FRTexture* pResource, const std::string& pPath)
{
}

void FR::FRTextureManager::DestroyResource(FRTexture* pResource)
{
	FRTextureLoader::Destroy(pResource);
}
