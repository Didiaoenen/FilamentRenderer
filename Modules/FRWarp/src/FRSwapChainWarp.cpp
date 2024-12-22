#include "FRSwapChainWarp.h"
#include "FREngineWarp.h"

FR::FRSwapChainWarp::FRSwapChainWarp(FREngineWarp* pEngine, void* pWindow)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createSwapChain(pWindow, filament::SwapChain::CONFIG_HAS_STENCIL_BUFFER));
}
