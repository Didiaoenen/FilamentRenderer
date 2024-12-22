#include "Core.FRCompositeRenderer.h"
#include "Core.FRARenderFeature.h"
#include "Core.FRView.h"

FR::FRCompositeRenderer::FRCompositeRenderer()
	: FRARenderer()
{
}

bool FR::FRCompositeRenderer::BeginFrame(const FRFrameDescriptor& pFrameDescriptor)
{
	for (const auto& [_, feature] : mFeatures)
	{
		if (feature->IsEnabled())
		{
			feature->OnBeginFrame();
		}
	}

	return FRARenderer::BeginFrame(pFrameDescriptor);
}

void FR::FRCompositeRenderer::DrawFrame(FRView* pView)
{
	FRARenderer::DrawFrame(pView);
}

void FR::FRCompositeRenderer::EndFrame()
{
	for (const auto& [_, feature] : mFeatures)
	{
		if (feature->IsEnabled())
		{
			feature->OnEndFrame();
		}
	}

	FRARenderer::EndFrame();
}
