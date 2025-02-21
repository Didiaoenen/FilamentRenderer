#include "FRRendererWarp.h"
#include "FRSwapChainWarp.h"
#include "FREngineWarp.h"
#include "FRViewWarp.h"

FR::FRRendererWarp::FRRendererWarp(FREngineWarp* pEngine)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createRenderer());
}

void FR::FRRendererWarp::SetClearOptions(const FClearOptions& pOptions)
{
	filament::Renderer::ClearOptions options;
	options.clear = pOptions.clear;
	options.discard = pOptions.discard;
	options.clearColor = { pOptions.clearColor.r, pOptions.clearColor.g, pOptions.clearColor.b, pOptions.clearColor.a };
	options.clearStencil = pOptions.clearStencil;
	PtrValue(this)->setClearOptions(options);
}

bool FR::FRRendererWarp::BeginFrame(FRSwapChainWarp* pSwapChain, uint64_t pVsyncSteadyClockTimeNano)
{
	return PtrValue(this)->beginFrame(PtrValue(pSwapChain), pVsyncSteadyClockTimeNano);
}

void FR::FRRendererWarp::Render(FRViewWarp* pView)
{
	PtrValue(this)->render(PtrValue(pView));
}

void FR::FRRendererWarp::EndFrame()
{
	PtrValue(this)->endFrame();
}
