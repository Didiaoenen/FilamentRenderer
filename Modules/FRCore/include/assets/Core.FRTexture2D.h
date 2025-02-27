#pragma once

#include "Core.FRAsset.h"
#include <FRTextureWarp.h>
#include <FRTextureSamplerWarp.h>

#include <string>
#include <vector>

namespace FR
{
	class FRImage;

	class FRTexture2D
		: public FRAsset
	{
		friend class FRTextureLoader;

	public:
		FRTexture2D() = default;
		
		FRTexture2D(FRTextureWarp* pTexture);

		FRTexture2D(FRImage* pImage,
			FRTextureWarp::EInternalFormat pInternalFormat = FRTextureWarp::EInternalFormat::RGBA8,
			FRTextureWarp::ESampler pType = FRTextureWarp::ESampler::SAMPLER_2D, std::vector<FRTextureWarp::EUsage> pUsages = { FRTextureWarp::EUsage::NONE });


		FRTexture2D(const uint32_t pWidth, const uint32_t pHeight,
			FRTextureWarp::EInternalFormat pInternalFormat = FRTextureWarp::EInternalFormat::RGBA8,
			FRTextureWarp::ESampler pType = FRTextureWarp::ESampler::SAMPLER_2D, std::vector<FRTextureWarp::EUsage> pUsages = { FRTextureWarp::EUsage::NONE });

		void InitSampler();

		void SetData(uint8_t* pData, uint32_t pSize);

		FRTextureSamplerWarp& GetSampler();

		FRTextureWarp* NativePtr();

	public:
		~FRTexture2D();

	private:
		FRImage* mImage{ nullptr };

		FRTextureWarp* mTexture{ nullptr };

		FRTextureSamplerWarp mSampler;

	};
}

