#include "Core.FRARenderer.h"

#include "Core.FRView.h"

#include <FRViewWarp.h>
#include <FRRendererWarp.h>
#include <FRSwapChainWarp.h>
#include <FRFilamentHelper.h>

namespace FR
{
	FRTexture* FRARenderer::mEmptyTexture = nullptr;
}

FR::FRARenderer::FRARenderer()
	: mIsDrawing(false)
{
	mRenderer = FRFilamentHelper::GetRenderer();
	mSwapChain = FRFilamentHelper::GetSwapChain();
}

bool FR::FRARenderer::BeginFrame(const FRFrameDescriptor& pFrameDescriptor)
{
	mFrameDescriptor = pFrameDescriptor;
	return mRenderer->BeginFrame(mSwapChain);
}

void FR::FRARenderer::DrawFrame(FRView* pView)
{
	mRenderer->Render(pView->NativePtr());
}

void FR::FRARenderer::EndFrame()
{
	mRenderer->EndFrame();
}

bool FR::FRARenderer::IsDrawing() const
{
	return false;
}

FR::FRARenderer::~FRARenderer()
{
}