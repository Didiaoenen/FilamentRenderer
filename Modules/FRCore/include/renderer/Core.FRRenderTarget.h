#pragma once

#include <FRRenderTargetWarp.h>

namespace FR
{
	class FRTexture2D;
	class FREngineWarp;

	class FRRenderTarget
	{
	public:
		FRRenderTarget();

		FRRenderTarget(FRTexture2D* mColorTexture, FRTexture2D* mDepthTexture);

		FRRenderTargetWarp* NativePtr();

	public:
		~FRRenderTarget();

	private:
		FRRenderTargetWarp* mRenderTarget{ nullptr };
	};
}

