#include "FRSceneWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"
#include "FRSkyboxWarp.h"
#include "FRIndirectLightWarp.h"

FR::FRSceneWarp::FRSceneWarp(FREngineWarp* pEngine)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createScene());
	pEngine->RegisterScene(this);
}

void FR::FRSceneWarp::AddEntity(FREntityWarp* pEntity)
{
	PtrValue(this)->addEntity(PtrValue(pEntity));
}

void FR::FRSceneWarp::SetSkybox(FRSkyboxWarp* pSkybox)
{
	PtrValue(this)->setSkybox(PtrValue(pSkybox));
}

void FR::FRSceneWarp::SetIndirectLight(FRIndirectLightWarp* pIndirectLight)
{
	PtrValue(this)->setIndirectLight(PtrValue(pIndirectLight));
}

void FR::FRSceneWarp::Remove(FREntityWarp* pEntity)
{
	PtrValue(this)->remove(PtrValue(pEntity));
}
