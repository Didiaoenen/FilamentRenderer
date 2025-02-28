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
		auto engine = FRFilamentHelper::GetEngine();
		FRTexture2D* texture = new FRTexture2D(new FRTextureWarp(engine, ktxBundle, false));
		texture->path = pPath;
		return texture;
	}
    return nullptr;
}

void FR::FRKtxManager::ReloadResource(FRTexture2D* pResource, const std::string& pPath)
{
}

void FR::FRKtxManager::DestroyResource(FRTexture2D* pResource)
{
}