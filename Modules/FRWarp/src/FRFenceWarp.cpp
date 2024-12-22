#include "FRFenceWarp.h"
#include "FREngineWarp.h"

FR::FRFenceWarp::FRFenceWarp(FREngineWarp* pEngine)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createFence());
}

filament::Fence::FenceStatus FR::FRFenceWarp::WaitAndDestroy(FRFenceWarp* pFence, filament::Fence::Mode pMode)
{
	return filament::Fence::waitAndDestroy(PtrValue(pFence), pMode);
}
