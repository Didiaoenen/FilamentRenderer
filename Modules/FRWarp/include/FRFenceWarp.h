#pragma once

#include "FRPtrWarp.h"
#include <filament/Fence.h>

namespace FR
{
	class FREngineWarp;

	class FRFenceWarp
		: public FRPtrWarp<filament::Fence>
	{
	public:
		FRFenceWarp() = default;

		FRFenceWarp(FREngineWarp* pEngine);

		static filament::Fence::FenceStatus WaitAndDestroy(FRFenceWarp* pFence, filament::Fence::Mode pMode = filament::Fence::Mode::FLUSH);
	
	};
}

