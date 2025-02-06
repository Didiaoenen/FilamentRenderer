#include "FRFenceWarp.h"
#include "FREngineWarp.h"

FR::FRFenceWarp::FRFenceWarp(FREngineWarp* pEngine)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createFence());
}

FR::FRFenceWarp::EFenceStatus FR::FRFenceWarp::WaitAndDestroy(FRFenceWarp* pFence, EMode pMode)
{
	return filament::Fence::waitAndDestroy(PtrValue(pFence), pMode);
}
