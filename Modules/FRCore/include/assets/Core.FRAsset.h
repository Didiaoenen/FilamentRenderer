#pragma once

#include "Core.FRObject.h"

#include <string>

namespace FR
{
    class FRAsset
        : public FRObject
    {
    public:
        FRAsset() = default;

    public:
        virtual ~FRAsset() = default;

    public:
        std::string path;

    };
}