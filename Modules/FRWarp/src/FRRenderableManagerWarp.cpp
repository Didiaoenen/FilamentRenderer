#include "FRRenderableManagerWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"

FR::FRRenderableManagerWarp::FRRenderableManagerWarp(FREngineWarp* pEngine)
{
	mValue = FRRefValue(PtrValue(pEngine)->getRenderableManager());
}

size_t FR::FRRenderableManagerWarp::GetPrimitiveCount(Instance pIinstance)
{
	return PtrValue(this).getPrimitiveCount(pIinstance.Ins());
}

void FR::FRRenderableManagerWarp::SetMaterialInstanceAt(Instance pInstance, size_t pPrimitiveIndex, FRMaterialInstanceWarp* pMaterialInstance)
{
	PtrValue(this).setMaterialInstanceAt(pInstance.Ins(), pPrimitiveIndex, PtrValue(pMaterialInstance));
}

void FR::FRRenderableManagerWarp::SetAxisAlignedBoundingBox(Instance pInstance, FRBoxWarp&& pAABB)
{
	PtrValue(this).setAxisAlignedBoundingBox(pInstance.Ins(), RefValue(pAABB));
}

FR::FRRenderableManagerWarp::Instance FR::FRRenderableManagerWarp::GetInstance(FREntityWarp* pEntity)
{
	return FR::FRRenderableManagerWarp::Instance(this, pEntity);
}

void FR::FRRenderableManagerWarp::Destroy(FREntityWarp* pEntity)
{
	PtrValue(this).destroy(PtrValue(pEntity));
}
