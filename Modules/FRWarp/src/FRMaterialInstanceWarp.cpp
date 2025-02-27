#include "FRMaterialInstanceWarp.h"
#include "FREngineWarp.h"
#include "FRTextureWarp.h"
#include "FRMaterialWarp.h"
#include "FRTextureSamplerWarp.h"
#include "FRFilamentHelper.h"

FR::FRMaterialInstanceWarp::FRMaterialInstanceWarp(FRMaterialWarp* pMaterial, const std::string& pName)
{
	mValue = FRPtrValue(PtrValue(pMaterial)->createInstance(pName.c_str()));
	FRFilamentHelper::GetEngine()->RegisterMaterial(this);
}

void FR::FRMaterialInstanceWarp::SetScissor(uint32_t pLeft, uint32_t pBottom, uint32_t pWidth, uint32_t pHeight)
{
	PtrValue(this)->setScissor(pLeft, pBottom, pWidth, pHeight);
}

void FR::FRMaterialInstanceWarp::SetParameter(const std::string& pName, FRTextureWarp* pTexture, FRTextureSamplerWarp& pSampler)
{
	PtrValue(this)->setParameter(pName.c_str(), PtrValue(pTexture), RefValue(pSampler));
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
