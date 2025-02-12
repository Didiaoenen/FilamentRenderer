#pragma once

#include "Core.FRImageParser.h"
#include <FRTextureSamplerWarp.h>

namespace FR
{
	class FRTexture;

	class FRTextureLoader
	{
	public:
		FRTextureLoader() = default;

		static FRTexture* Create(const std::string& pFilepath,
			FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter, bool pGenerateMipmap);

		static FRTexture* CreatePixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		static FRTexture* CreateFromMemory(uint8_t* pData, uint32_t pWidth, uint32_t pHeight,
			FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter pSecondFilter, bool pGenerateMipmap);

		//static void Reload(Texture& pTexture, const std::string& pFilePath, ETextureFilteringMode pFirstFilter, ETextureFilteringMode pSecondFilter, bool pGenerateMipmap);

		static bool Destroy(FRTexture*& pTextureInstance);

	public:
		~FRTextureLoader() = default;

	private:
		static FRImageParser __STBI;

	};
}

