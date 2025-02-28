#pragma once

#include "FRPtrWarp.h"
#include <filament/Texture.h>

namespace FR
{
	class FREngineWarp;
	class FRKtx1BundleWarp;
	class FRPixelBufferDescriptorWarp;

	class FRTextureWarp
		: public FRPtrWarp<filament::Texture>
	{
	public:
		using EType = filament::Texture::Type;
		
		using EUsage = filament::Texture::Usage;

		using EFormat = filament::Texture::Format;

		using ESampler = filament::Texture::Sampler;

		using EInternalFormat = filament::Texture::InternalFormat;

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

			Builder& Usage(EUsage usage)
			{
				mBuilder.usage(usage);
				return *this;
			}

			Builder& Format(EInternalFormat pFormat)
			{
				mBuilder.format(pFormat);
				return *this;
			}

			Builder& Sampler(ESampler pTarget)
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

		FRTextureWarp(FREngineWarp* pEngine, FRKtx1BundleWarp* pKtxBundle, bool pSRGB);

		void SetImage(FREngineWarp* pEngine, size_t pLevel, FRPixelBufferDescriptorWarp&& buffer);

		void GenerateMipmaps(FREngineWarp* pEngine);

		FRKtx1BundleWarp* GetKtxBundle();

		size_t GetWidth();

		size_t GetHeight();

	public:
		virtual ~FRTextureWarp();

	private:
		FRKtx1BundleWarp* mKtx1Bundle{ nullptr };

	};
}

