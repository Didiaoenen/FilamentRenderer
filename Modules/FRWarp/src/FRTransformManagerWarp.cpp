#include "FRTransformManagerWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"
#include <MathConvert.h>

FR::FRTransformManagerWarp::FRTransformManagerWarp(FREngineWarp* pEngine)
{
	mValue = FRRefValue(PtrValue(pEngine)->getTransformManager());
}

void FR::FRTransformManagerWarp::SetTransform(Instance pInstance, const glm::mat4& pLocalTransform)
{
	PtrValue(this).setTransform(pInstance.Ins(), MathConvert::ToFMat4(pLocalTransform));
}

void FR::FRTransformManagerWarp::Create(FREntityWarp* pEntity, Instance pParent, const glm::mat4& pLocalTransform)
{
	PtrValue(this).create(PtrValue(pEntity), pParent.Ins(), MathConvert::ToFMat4(pLocalTransform));
}

void FR::FRTransformManagerWarp::SetParent(Instance pInstance, Instance pParent)
{
	PtrValue(this).setParent(pInstance.Ins(), pParent.Ins());
}

FR::FRTransformManagerWarp::Instance FR::FRTransformManagerWarp::GetInstance(FREntityWarp* pEntity)
{
	return FRTransformManagerWarp::Instance(this, pEntity);
}

void FR::FRTransformManagerWarp::Destroy(FREntityWarp* pEntity)
{
	PtrValue(this).destroy(PtrValue(pEntity));
}
