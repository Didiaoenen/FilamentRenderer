#pragma once

#include <FRRenderTargetWarp.h>

namespace FR
{
	class FRTexture;
	class FREngineWarp;

	class FRRenderTarget
	{
	public:
		FRRenderTarget();

		FRRenderTarget(FRTexture* mColorTexture, FRTexture* mDepthTexture);

		FRRenderTargetWarp* NativePtr();

	public:
		~FRRenderTarget();

	private:
		FRRenderTargetWarp* mRenderTarget{ nullptr };
	};
}

