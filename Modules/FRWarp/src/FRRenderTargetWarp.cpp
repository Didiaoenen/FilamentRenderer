#include "FRRenderTargetWarp.h"
#include "FREngineWarp.h"

FR::FRRenderTargetWarp::FRRenderTargetWarp(FREngineWarp* pEngine, Builder* mBuilder)
{
	mValue = FRPtrValue(mBuilder->mBuilder.build(*PtrValue(pEngine)));
}
