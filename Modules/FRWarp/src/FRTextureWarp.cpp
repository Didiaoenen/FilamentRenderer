#include "FRTextureWarp.h"
#include "FREngineWarp.h"
#include "FRPixelBufferDescriptorWarp.h"

FR::FRTextureWarp::FRTextureWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
}

void FR::FRTextureWarp::SetImage(FREngineWarp* pEngine, size_t pLevel, FRPixelBufferDescriptorWarp&& pBuffer)
{
	PtrValue(this)->setImage(*PtrValue(pEngine), pLevel, std::move(RefValue(pBuffer)));
}

void FR::FRTextureWarp::GenerateMipmaps(FREngineWarp* pEngine)
{
	PtrValue(this)->generateMipmaps(*PtrValue(pEngine));
}
