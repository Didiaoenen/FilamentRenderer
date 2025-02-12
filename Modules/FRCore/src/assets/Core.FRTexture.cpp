#include "Core.FRTexture.h"

#include <FREngineWarp.h>
#include <FRTextureWarp.h>
#include <FRFilamentHelper.h>
#include <FRTextureSamplerWarp.h>
#include <FRPixelBufferDescriptorWarp.h>

FR::FRTexture::FRTexture(const std::string& pPath)
	: path(pPath)
{
}

FR::FRTexture::FRTexture(const uint32_t pWidth, const uint32_t pHeight,
	FRTextureWarp::EInternalFormat pInternalFormat, FRTextureWarp::ESampler pType, std::vector<FRTextureWarp::EUsage> pUsages)
{
	width = pWidth;
	height = pHeight;

	auto usages = FRTextureWarp::EUsage::NONE;
	for (const auto usage : pUsages)
	{
		usages |= usage;
	}

	auto engine = FRFilamentHelper::GetEngine();
	mTexture = FRTextureWarp::Builder()
		.Width(pWidth).Height(pHeight).Levels(mipCount).Usage(usages)
		.Format(pInternalFormat)
		.Sampler(pType)
		.Build(engine);
}

void FR::FRTexture::SetData(void* pData, uint32_t pSize)
{
	auto engine = FRFilamentHelper::GetEngine();
	FRPixelBufferDescriptorWarp buffer(pData, pSize, FRTextureWarp::EFormat::RGBA, FRTextureWarp::EType::UBYTE);
	mTexture->SetImage(engine, 0, std::move(buffer));
	mTexture->GenerateMipmaps(engine);
}

FR::FRTextureSamplerWarp& FR::FRTexture::GetSampler()
{
	return mSampler;
}

void FR::FRTexture::SetSampler()
{	
	mSampler = FRTextureSamplerWarp();
	mSampler.SetMinFilter(FRTextureSamplerWarp::EMinFilter::LINEAR_MIPMAP_LINEAR);
	mSampler.SetMagFilter(FRTextureSamplerWarp::EMagFilter::LINEAR);
	mSampler.SetWrapModeS(FRTextureSamplerWarp::EWrapMode::REPEAT);
	mSampler.SetWrapModeT(FRTextureSamplerWarp::EWrapMode::REPEAT);
}

FR::FRTextureWarp* FR::FRTexture::NativePtr()
{
	return mTexture;
}

FR::FRTexture::~FRTexture()
{
	FRFilamentHelper::GetEngine()->Destroy(mTexture);
	mTexture = nullptr;
}