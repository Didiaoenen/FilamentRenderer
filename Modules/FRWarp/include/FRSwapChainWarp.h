#pragma once

#include "FRPtrWarp.h"
#include <filament/SwapChain.h>

namespace FR
{
	class FREngineWarp;

	class FRSwapChainWarp
		: public FRPtrWarp<filament::SwapChain>
	{
	public:
		FRSwapChainWarp() = default;

		FRSwapChainWarp(FREngineWarp* pEngine, void* pWindow);

	public:
		virtual ~FRSwapChainWarp();

	};
}

