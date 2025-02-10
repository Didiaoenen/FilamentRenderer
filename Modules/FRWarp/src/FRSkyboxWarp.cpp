#include "FRSkyboxWarp.h"
#include "FREngineWarp.h"

FR::FRSkyboxWarp::FRSkyboxWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
	pEngine->RegisterSkybox(this);
}
