#pragma once

#include "FRPtrWarp.h"
#include <filament/Texture.h>

namespace FR
{
	class FREngineWarp;
	class FRPixelBufferDescriptorWarp;

	class FRTextureWarp
		: public FRPtrWarp<filament::Texture>
	{
	public:

		class Builder
		{
			friend class FRTextureWarp;

		public:
			Builder()
				: mBuilder()
			{

			}

			Builder& Width(uint32_t pWidth)
			{
				mBuilder.width(pWidth);
				return *this;
			}

			Builder& Height(uint32_t pHeight)
			{
				mBuilder.height(pHeight);
				return *this;
			}

			Builder& Levels(uint8_t pLevels)
			{
				mBuilder.levels(pLevels);
				return *this;
			}

			Builder& Usage(filament::Texture::Usage usage)
			{
				mBuilder.usage(usage);
				return *this;
			}

			Builder& Format(filament::Texture::InternalFormat pFormat)
			{
				mBuilder.format(pFormat);
				return *this;
			}

			Builder& Sampler(filament::Texture::Sampler pTarget)
			{
				mBuilder.sampler(pTarget);
				return *this;
			}

			FRTextureWarp* Build(FREngineWarp* pEngine)
			{
				return new FRTextureWarp(pEngine, this);
			}

		private:
			filament::Texture::Builder mBuilder;
		};

		FRTextureWarp() = default;

		FRTextureWarp(FREngineWarp* pEngine, Builder* pBuilder);

		void SetImage(FREngineWarp* pEngine, size_t pLevel, FRPixelBufferDescriptorWarp&& buffer);

		void GenerateMipmaps(FREngineWarp* pEngine);

	};
}

