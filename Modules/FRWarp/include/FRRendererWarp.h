#pragma once

#include "FRPtrWarp.h"
#include <filament/Renderer.h>
#include <Color.h>

namespace FR
{
	class FRViewWarp;
	class FREngineWarp;
	class FRSwapChainWarp;

	class FRRendererWarp
		: public FRPtrWarp<filament::Renderer>
	{
	public:
        struct FClearOptions
		{
			Color clearColor = {};

            uint8_t clearStencil = 0u;

            bool clear = false;

            bool discard = true;
        };

		FRRendererWarp() = default;

		FRRendererWarp(FREngineWarp* pEngine);

		void SetClearOptions(const FClearOptions& pOptions);

		bool BeginFrame(FRSwapChainWarp* pSwapChain, uint64_t pVsyncSteadyClockTimeNano = 0u);

		void Render(FRViewWarp* pView);

		void EndFrame();

	};
}

