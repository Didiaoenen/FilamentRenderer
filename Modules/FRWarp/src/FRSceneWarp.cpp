#include "FRSceneWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"

FR::FRSceneWarp::FRSceneWarp(FREngineWarp* pEngine)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createScene());
}

void FR::FRSceneWarp::AddEntity(FREntityWarp* pEntity)
{
	PtrValue(this)->addEntity(PtrValue(pEntity));
}

void FR::FRSceneWarp::SetSkybox(filament::Skybox* skybox)
{
	PtrValue(this)->setSkybox(skybox);
}

void FR::FRSceneWarp::SetIndirectLight(filament::IndirectLight* ibl)
{
	PtrValue(this)->setIndirectLight(ibl);
}

void FR::FRSceneWarp::Remove(FREntityWarp* pEntity)
{
	PtrValue(this)->remove(PtrValue(pEntity));
}
