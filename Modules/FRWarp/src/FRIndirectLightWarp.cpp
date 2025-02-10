#include "FRIndirectLightWarp.h"

#include "FREngineWarp.h"

FR::FRIndirectLightWarp::FRIndirectLightWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
}
