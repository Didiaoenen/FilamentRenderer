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
		using EMode = filament::Fence::Mode;

		using EFenceStatus = filament::Fence::FenceStatus;

		FRFenceWarp() = default;

		FRFenceWarp(FREngineWarp* pEngine);

		static EFenceStatus WaitAndDestroy(FRFenceWarp* pFence, EMode pMode = EMode::FLUSH);
	
	};
}

