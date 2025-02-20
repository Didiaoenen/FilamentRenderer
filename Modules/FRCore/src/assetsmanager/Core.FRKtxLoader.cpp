#include "Core.FRKtxLoader.h"

#include <FRKtx1BundleWarp.h>

#include <Tools.FRFile.h>

FR::FRKtx1BundleWarp* FR::FRKtxLoader::Create(const std::string& pFilePath)
{
    auto data = FRFile::ReadBinaryFile(pFilePath);
    if (data.size() > 0)
    {
        return new FRKtx1BundleWarp(data.data(), data.size());
    }
    return nullptr;
}

void FR::FRKtxLoader::Destroy(FRKtx1BundleWarp*& pKtxBundle)
{
}
