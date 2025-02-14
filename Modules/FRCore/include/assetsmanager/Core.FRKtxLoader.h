#pragma once

#include <string>

namespace FR
{
    class FRKtx1BundleWarp;

    class FRKtxLoader
    {
    public:
        FRKtxLoader() = default;

        static FRKtx1BundleWarp* Create(const std::string& pFilePath);

        static bool Destroy(FRKtx1BundleWarp*& pKtxBundle);
        
    };
}