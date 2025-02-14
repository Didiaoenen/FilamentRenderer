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
	pEngine->RegisterTexture(this);
}

void FR::FRTextureWarp::SetImage(FREngineWarp* pEngine, size_t pLevel, FRPixelBufferDescriptorWarp&& pBuffer)
{
	PtrValue(this)->setImage(*PtrValue(pEngine), pLevel, std::move(RefValue(pBuffer)));
}

void FR::FRTextureWarp::GenerateMipmaps(FREngineWarp* pEngine)
{
	PtrValue(this)->generateMipmaps(*PtrValue(pEngine));
}

size_t FR::FRTextureWarp::GetWidth()
{
	return PtrValue(this)->getWidth();
}

size_t FR::FRTextureWarp::GetHeight()
{
	return PtrValue(this)->getHeight();
}
