#include "FRTextureWarp.h"
#include "FREngineWarp.h"
#include "FRKtx1BundleWarp.h"
#include "FRPixelBufferDescriptorWarp.h"

#include <ktxreader/Ktx1Reader.h>

FR::FRTextureWarp::FRTextureWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
	pEngine->RegisterTexture(this);
}

FR::FRTextureWarp::FRTextureWarp(FREngineWarp* pEngine, FRKtx1BundleWarp* pKtxBundle, bool pSRGB)
{
	mValue = FRPtrValue(ktxreader::Ktx1Reader::createTexture(PtrValue(pEngine), PtrValue(pKtxBundle), pSRGB));
	mKtx1Bundle = pKtxBundle;
	pEngine->RegisterTexture(this);
	pEngine->RegisterFRKtx1Bundle(pKtxBundle);
}

void FR::FRTextureWarp::SetImage(FREngineWarp* pEngine, size_t pLevel, FRPixelBufferDescriptorWarp&& pBuffer)
{
	PtrValue(this)->setImage(*PtrValue(pEngine), pLevel, std::move(RefValue(pBuffer)));
}

void FR::FRTextureWarp::GenerateMipmaps(FREngineWarp* pEngine)
{
	PtrValue(this)->generateMipmaps(*PtrValue(pEngine));
}

FR::FRKtx1BundleWarp* FR::FRTextureWarp::GetKtxBundle()
{
	return mKtx1Bundle;
}

size_t FR::FRTextureWarp::GetWidth()
{
	return PtrValue(this)->getWidth();
}

size_t FR::FRTextureWarp::GetHeight()
{
	return PtrValue(this)->getHeight();
}

FR::FRTextureWarp::~FRTextureWarp() = default;
