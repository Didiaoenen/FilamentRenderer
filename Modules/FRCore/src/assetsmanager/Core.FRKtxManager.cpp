#include "Core.FRKtxManager.h"
#include "Core.FRKtxLoader.h"
#include "Core.FRTexture.h"

#include <FRFilamentHelper.h>
#include <FRKtx1BundleWarp.h>
#include <Tools.FRPathUtils.h>

FR::FRTexture* FR::FRKtxManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (FRKtx1BundleWarp* ktxBundle = FRKtxLoader::Create(realPath))
	{
		FRTexture* texture = new FRTexture(new FRTextureWarp(FRFilamentHelper::GetEngine(), ktxBundle, false));
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(texture) + offsetof(FRTexture, path)) = pPath;
		return texture;
	}
    return nullptr;
}

void FR::FRKtxManager::DestroyResource(FRTexture* pResource)
{
}

void FR::FRKtxManager::ReloadResource(FRTexture* pResource, const std::string& pPath)
{
}
