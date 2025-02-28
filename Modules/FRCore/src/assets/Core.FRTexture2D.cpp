#include "Core.FRTexture2D.h"
#include "Core.FRImage.h"

#include <FREngineWarp.h>
#include <FRTextureWarp.h>
#include <FRFilamentHelper.h>
#include <FRTextureSamplerWarp.h>
#include <FRPixelBufferDescriptorWarp.h>

FR::FRTexture2D::FRTexture2D(FRTextureWarp* pTexture)
{
	mTexture = pTexture;
}

FR::FRTexture2D::FRTexture2D(FRImage* pImage,
	FRTextureWarp::EInternalFormat pInternalFormat, FRTextureWarp::ESampler pType, std::vector<FRTextureWarp::EUsage> pUsages)
	: mImage(pImage)
{
	auto usages = FRTextureWarp::EUsage::NONE;
	for (const auto usage : pUsages)
	{
		usages |= usage;
	}

	auto engine = FRFilamentHelper::GetEngine();
	mTexture = FRTextureWarp::Builder()
		.Width(mImage->width).Height(mImage->height).Levels(mImage->mipCount).Usage(usages)
		.Format(pInternalFormat)
		.Sampler(pType)
		.Build(engine);

	SetImage(mImage);
}

FR::FRTexture2D::FRTexture2D(const uint32_t pWidth, const uint32_t pHeight,
	FRTextureWarp::EInternalFormat pInternalFormat, FRTextureWarp::ESampler pType, std::vector<FRTextureWarp::EUsage> pUsages)
{
	auto usages = FRTextureWarp::EUsage::NONE;
	for (const auto usage : pUsages)
	{
		usages |= usage;
	}

	auto engine = FRFilamentHelper::GetEngine();
	mTexture = FRTextureWarp::Builder()
		.Width(pWidth).Height(pHeight).Levels(1).Usage(usages)
		.Format(pInternalFormat)
		.Sampler(pType)
		.Build(engine);
}

void FR::FRTexture2D::InitSampler()
{
	mSampler = FRTextureSamplerWarp();
	mSampler.SetMinFilter(FRTextureSamplerWarp::EMinFilter::LINEAR_MIPMAP_LINEAR);
	mSampler.SetMagFilter(FRTextureSamplerWarp::EMagFilter::LINEAR);
	mSampler.SetWrapModeS(FRTextureSamplerWarp::EWrapMode::REPEAT);
	mSampler.SetWrapModeT(FRTextureSamplerWarp::EWrapMode::REPEAT);
}

void FR::FRTexture2D::SetImage(FRImage* pImage)
{
	mImage = pImage;

	auto engine = FRFilamentHelper::GetEngine();
	FRPixelBufferDescriptorWarp buffer(mImage->data, mImage->size, FRTextureWarp::EFormat::RGBA, FRTextureWarp::EType::UBYTE);
	mTexture->SetImage(engine, 0, std::move(buffer));
	mTexture->GenerateMipmaps(engine);
}

void FR::FRTexture2D::SetData(uint8_t* pData, uint32_t pSize)
{
	auto engine = FRFilamentHelper::GetEngine();
	FRPixelBufferDescriptorWarp buffer(pData, pSize, FRTextureWarp::EFormat::RGBA, FRTextureWarp::EType::UBYTE);
	mTexture->SetImage(engine, 0, std::move(buffer));
	mTexture->GenerateMipmaps(engine);
}

FR::FRTextureSamplerWarp& FR::FRTexture2D::GetSampler()
{
	return mSampler;
}

FR::FRTextureWarp* FR::FRTexture2D::NativePtr()
{
	return mTexture;
}

FR::FRTexture2D::~FRTexture2D()
{
	FRFilamentHelper::GetEngine()->Destroy(mTexture);
	FRFilamentHelper::GetEngine()->UnRegisterTexture(mTexture);
	delete mTexture; mTexture = nullptr;
}