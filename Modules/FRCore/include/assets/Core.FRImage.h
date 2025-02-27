#pragma once

#include "Core.FRAsset.h"

namespace FR
{
    class FRImage
        : public FRAsset
    {
    public:
        FRImage() = default;

    public:
        virtual ~FRImage() = default;

    public:
        uint8_t* data{ nullptr };

        uint32_t size{ 0 };

		uint32_t width{ 0 };
		
        uint32_t height{ 0 };
		
        uint32_t mipCount{ 1 };
        bool isMimapped{ false };
		
        uint32_t bitsPerPixel{ 8 };

    };
}