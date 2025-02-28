#pragma once

#include "Core.FRImageParser.h"
#include <FRTextureSamplerWarp.h>

namespace FR
{
	class FRTexture2D;

	class FRTextureLoader
	{
	public:
		static FRTexture2D* Create(const std::string& pFilePath,
			FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter, bool pGenerateMipmap);

		static FRTexture2D* CreatePixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		static FRTexture2D* CreateFromMemory(uint8_t* pData, uint32_t pSize, uint32_t pWidth, uint32_t pHeight,
			FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter pSecondFilter, bool pGenerateMipmap);

		static void Reload(FRTexture2D* pTexture, const std::string& pFilePath,
			FRTextureSamplerWarp::EMinFilter pFirstFilter, FRTextureSamplerWarp::EMagFilter pSecondFilter, bool pGenerateMipmap);

		static void Destroy(FRTexture2D*& pTexture);

	private:
		inline static FRImageParser __STBI;

	};
}

