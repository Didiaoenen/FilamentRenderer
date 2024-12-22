#pragma once

#include <string>
#include <vector>
#include <FRTextureWarp.h>
#include <FRTextureSamplerWarp.h>
#include "Core.FRObject.h"
#include "ETextureDefine.h"

namespace FR
{
	class FRTexture
		: public FRObject
	{
		friend class FRTextureLoader;

	public:
		FRTexture(const std::string& pPath);

		FRTexture(const uint32_t pWidth, const uint32_t pHeight,
			ETexture::EInternalFormat pInternalFormat = ETexture::EInternalFormat::RGBA8,
			ETexture::ESampler pType = ETexture::ESampler::SAMPLER_2D, std::vector<ETexture::EUsage> pUsages = { ETexture::EUsage::NONE });

		void SetData(void* pData, uint32_t pSize);

		FRTextureSamplerWarp& GetSampler();

		void SetSampler();

		FRTextureWarp* NativePtr();

	public:
		~FRTexture();

	public:
		std::string path;

		uint32_t width;
		uint32_t height;
		//bool isMimapped;
		//uint32_t bitsPerPixel;
		//ETextureFilteringMode firstFilter;
		//ETextureFilteringMode secondFilter;

		uint32_t mipCount = 1;

	private:
		FRTextureWarp* mTexture{ nullptr };
		FRTextureSamplerWarp mSampler;

	};
}

