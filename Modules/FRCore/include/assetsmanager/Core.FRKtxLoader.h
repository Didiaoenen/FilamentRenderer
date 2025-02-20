#pragma once

#include <string>

namespace FR
{
    class FRKtx1BundleWarp;

    class FRKtxLoader
    {
    public:
        static FRKtx1BundleWarp* Create(const std::string& pFilePath);

        static void Destroy(FRKtx1BundleWarp*& pKtxBundle);
        
    };
}