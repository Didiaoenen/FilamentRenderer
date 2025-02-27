#pragma once

#include "Core.RFIRenderer.h"

namespace FR
{
	class FRView;
	class FRTexture2D;
	class FRRendererWarp;
	class FRSwapChainWarp;

	class FRARenderer
		: public RFIRenderer
	{
	public:
		FRARenderer();

		virtual bool BeginFrame(const FRFrameDescriptor& pFrameDescriptor);

		virtual void DrawFrame(FRView* pView);

		virtual void EndFrame();

		bool IsDrawing() const;

	public:
		virtual ~FRARenderer();

	protected:
		bool mIsDrawing{ false };
		FRRendererWarp* mRenderer{ nullptr };
		FRSwapChainWarp* mSwapChain{ nullptr };

		FRFrameDescriptor mFrameDescriptor;

	};
}

