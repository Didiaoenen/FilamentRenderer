#pragma once

#include "Core.FRAsset.h"

namespace FR
{
    class FRImage
        : public FRAsset
    {
    public:
        FRImage() = default;

        FRImage(uint8_t* pData, uint32_t pSize, uint32_t pWidth, uint32_t pHeight);

    public:
        virtual ~FRImage();

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