#pragma once

#include "FRPtrWarp.h"
#include <image/Ktx1Bundle.h>

#include <cstdint>

namespace FR
{
    class FRKtx1BundleWarp
        : public FRPtrWarp<image::Ktx1Bundle>
    {
    public:
        FRKtx1BundleWarp() = default;

        FRKtx1BundleWarp(uint8_t const* pData, uint32_t pCount);

    public:
        virtual ~FRKtx1BundleWarp();

    };
}