#include "Core.FRKtxManager.h"
#include "Core.FRKtxLoader.h"
#include "Core.FRTexture2D.h"

#include <FRFilamentHelper.h>
#include <FRKtx1BundleWarp.h>
#include <Tools.FRPathUtils.h>

FR::FRTexture2D* FR::FRKtxManager::CreateResource(const std::string& pPath)
{
	std::string realPath = FRPathUtils::GetRealPath(pPath);
	if (FRKtx1BundleWarp* ktxBundle = FRKtxLoader::Create(realPath))
	{
		FRTexture2D* texture = new FRTexture2D(new FRTextureWarp(FRFilamentHelper::GetEngine(), ktxBundle, false));
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(texture) + offsetof(FRTexture2D, path)) = pPath;
		return texture;
	}
    return nullptr;
}

void FR::FRKtxManager::DestroyResource(FRTexture2D* pResource)
{
}

void FR::FRKtxManager::ReloadResource(FRTexture2D* pResource, const std::string& pPath)
{
}
