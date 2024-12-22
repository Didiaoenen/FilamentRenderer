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
	ETexture::EInternalFormat pInternalFormat, ETexture::ESampler pType, std::vector<ETexture::EUsage> pUsages)
{
	width = pWidth;
	height = pHeight;

	auto usages = ConvertEnum(ETexture::EUsage::NONE);
	for (const auto usage : pUsages)
	{
		usages |= ConvertEnum(usage);
	}

	auto engine = FRFilamentHelper::GetEngine();
	mTexture = FRTextureWarp::Builder()
		.Width(pWidth).Height(pHeight).Levels(mipCount).Usage(usages)
		.Format(ConvertEnum(pInternalFormat))
		.Sampler(ConvertEnum(pType))
		.Build(engine);
}

void FR::FRTexture::SetData(void* pData, uint32_t pSize)
{
	auto engine = FRFilamentHelper::GetEngine();
	FRPixelBufferDescriptorWarp buffer(pData, pSize, ConvertEnum(ETexture::EFormat::RGBA), ConvertEnum(ETexture::EType::UBYTE));
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
	mSampler.SetMinFilter(ConvertEnum(ETexture::EMinFilter::LINEAR_MIPMAP_LINEAR));
	mSampler.SetMagFilter(ConvertEnum(ETexture::EMagFilter::LINEAR));
	mSampler.SetWrapModeS(ConvertEnum(ETexture::EWrapMode::REPEAT));
	mSampler.SetWrapModeT(ConvertEnum(ETexture::EWrapMode::REPEAT));
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