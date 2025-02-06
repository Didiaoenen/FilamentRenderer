#include "FRMaterialInstanceWarp.h"
#include "FRTextureWarp.h"
#include "FRMaterialWarp.h"
#include "FRTextureSamplerWarp.h"

FR::FRMaterialInstanceWarp::FRMaterialInstanceWarp(FRMaterialWarp* pMaterial, const char* pName)
{
	mValue = FRPtrValue(PtrValue(pMaterial)->createInstance(pName));
}

void FR::FRMaterialInstanceWarp::SetScissor(uint32_t pLeft, uint32_t pBottom, uint32_t pWidth, uint32_t pHeight)
{
	PtrValue(this)->setScissor(pLeft, pBottom, pWidth, pHeight);
}

void FR::FRMaterialInstanceWarp::SetParameter(const char* pName, FRTextureWarp* pTexture, FRTextureSamplerWarp& pSampler)
{
	PtrValue(this)->setParameter(pName, PtrValue(pTexture), RefValue(pSampler));
}

void FR::FRMaterialInstanceWarp::SetTransparencyMode(ETransparencyMode pMode)
{
	PtrValue(this)->setTransparencyMode(pMode);
}

void FR::FRMaterialInstanceWarp::SetCullingMode(ECullingMode pCulling)
{
	PtrValue(this)->setCullingMode(pCulling);
}

void FR::FRMaterialInstanceWarp::SetDepthCulling(bool pEnable)
{
	PtrValue(this)->setDepthCulling(pEnable);
}

void FR::FRMaterialInstanceWarp::SetColorWrite(bool pEnable)
{
	PtrValue(this)->setColorWrite(pEnable);
}

void FR::FRMaterialInstanceWarp::SetDepthWrite(bool pEnable)
{
	PtrValue(this)->setDepthWrite(pEnable);
}
