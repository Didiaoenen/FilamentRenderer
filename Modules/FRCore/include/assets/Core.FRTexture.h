#pragma once

#include "Core.FRObject.h"
#include <FRTextureWarp.h>
#include <FRTextureSamplerWarp.h>

#include <string>
#include <vector>

namespace FR
{
	class FRTexture
		: public FRObject
	{
		friend class FRTextureLoader;

	public:
		FRTexture() = default;
		
		FRTexture(const std::string& pPath);

		FRTexture(const uint32_t pWidth, const uint32_t pHeight,
			FRTextureWarp::EInternalFormat pInternalFormat = FRTextureWarp::EInternalFormat::RGBA8,
			FRTextureWarp::ESampler pType = FRTextureWarp::ESampler::SAMPLER_2D, std::vector<FRTextureWarp::EUsage> pUsages = { FRTextureWarp::EUsage::NONE });

		FRTexture(FRTextureWarp* pTexture);

		void SetData(void* pData, uint32_t pSize);

		FRTextureSamplerWarp& GetSampler();

		void SetSampler();

		FRTextureWarp* NativePtr();

	public:
		~FRTexture();

	public:
		std::string path;

		uint32_t width{ 0 };
		uint32_t height{ 0 };
		//bool isMimapped;
		//uint32_t bitsPerPixel;
		//ETextureFilteringMode firstFilter;
		//ETextureFilteringMode secondFilter;

		uint32_t mipCount{ 1 };

	private:
		FRTextureWarp* mTexture{ nullptr };

		FRTextureSamplerWarp mSampler;

	};
}

