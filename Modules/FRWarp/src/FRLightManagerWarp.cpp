#include "FRLightManagerWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"
#include <MathConvert.h>

FR::FRLightManagerWarp::FRLightManagerWarp(FREngineWarp* pEngine)
{
	mValue = FRRefValue(PtrValue(pEngine)->getLightManager());
}

void FR::FRLightManagerWarp::SetPosition(Instance pInstance, const glm::vec3& pPosition)
{
	PtrValue(this).setPosition(pInstance.Ins(), MathConvert::ToFVec3(pPosition));
}

void FR::FRLightManagerWarp::SetDirection(Instance pInstance, const glm::vec3& pDirection)
{
	PtrValue(this).setDirection(pInstance.Ins(), MathConvert::ToFVec3(pDirection));
}

void FR::FRLightManagerWarp::SetColor(Instance pInstance, const Color& pColor)
{
	PtrValue(this).setColor(pInstance.Ins(), { pColor.x, pColor.y, pColor.z });
}

void FR::FRLightManagerWarp::SetFalloff(Instance pInstance, float pRadius)
{
	PtrValue(this).setFalloff(pInstance.Ins(), pRadius);
}

void FR::FRLightManagerWarp::SetIntensity(Instance pInstance, float pIntensity)
{
	PtrValue(this).setIntensity(pInstance.Ins(), pIntensity);
}

void FR::FRLightManagerWarp::SetIntensity(Instance pInstance, float pIntensity, float pEfficiency)
{
	PtrValue(this).setIntensity(pInstance.Ins(), pIntensity, pEfficiency);
}

void FR::FRLightManagerWarp::SetIntensityCandela(Instance pInstance, float pIntensity)
{
	PtrValue(this).setIntensityCandela(pInstance.Ins(), pIntensity);
}

void FR::FRLightManagerWarp::SetShadowCaster(Instance pInstance, bool pShadowCaster)
{
	PtrValue(this).setShadowCaster(pInstance.Ins(), pShadowCaster);
}

void FR::FRLightManagerWarp::SetSpotLightCone(Instance pInstance, float pInner, float pOuter)
{
	PtrValue(this).setSpotLightCone(pInstance.Ins(), pInner, pOuter);
}

void FR::FRLightManagerWarp::SetSunAngularRadius(Instance pInstance, bool pSunAngular)
{
	PtrValue(this).setSunAngularRadius(pInstance.Ins(), pSunAngular);
}

FR::FRLightManagerWarp::Instance FR::FRLightManagerWarp::GetInstance(FREntityWarp* pEntity)
{
	return Instance(this, pEntity);
}

void FR::FRLightManagerWarp::Destroy(FREntityWarp* pEntity)
{
	PtrValue(this).destroy(PtrValue(pEntity));
}
