#include "FRCameraWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"
#include <MathConvert.h>

FR::FRCameraWarp::FRCameraWarp(FREngineWarp* pEngine, FREntityWarp* pEntity)
	: mEntity(pEntity)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createCamera(PtrValue(pEntity)));
}

void FR::FRCameraWarp::LookAt(glm::vec3 const& pEye, glm::vec3 const& pCenter, glm::vec3 const& pUp)
{
	PtrValue(this)->lookAt(MathConvert::ToFVec3(pEye), MathConvert::ToFVec3(pCenter), MathConvert::ToFVec3(pUp));
}

void FR::FRCameraWarp::SetProjection(filament::Camera::Projection pProjection, double pLeft, double pRight, double pBottom, double pTop, double pNear, double pFar)
{
	PtrValue(this)->setProjection(pProjection, pLeft, pRight, pBottom, pTop, pNear, pFar);
}

void FR::FRCameraWarp::SetProjection(double pFovInDegrees, double pAspect, double pNear, double pFar, filament::Camera::Fov pDirection)
{
	PtrValue(this)->setProjection(pFovInDegrees, pAspect, pNear, pFar, pDirection);
}

void FR::FRCameraWarp::SetExposure(float pAperture, float pShutterSpeed, float pSensitivity)
{
	PtrValue(this)->setExposure(pAperture, pShutterSpeed, pSensitivity);
}

void FR::FRCameraWarp::SetScaling(glm::vec2 pScaling)
{
	PtrValue(this)->setScaling({ pScaling.x, pScaling.y });
}

FR::FREntityWarp* FR::FRCameraWarp::GetEntity()
{
	return mEntity;
}

glm::mat4 FR::FRCameraWarp::GetViewMatrix()
{
	return MathConvert::ToGlmMat4(PtrValue(this)->getViewMatrix());
}

glm::mat4 FR::FRCameraWarp::GetProjectionMatrix()
{
	return MathConvert::ToGlmMat4(PtrValue(this)->getProjectionMatrix());
}
