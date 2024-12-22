#pragma once

#include "FRPtrWarp.h"
#include "FRTextureWarp.h"
#include "EAttachmentPoint.h"
#include <filament/RenderTarget.h>

namespace FR
{
	class FREngineWarp;

	class FRRenderTargetWarp
		: public FRPtrWarp<filament::RenderTarget>
	{
	public:

		class Builder
		{
			friend class FRRenderTargetWarp;

		public:
			Builder()
				: mBuilder()
			{
			}

			Builder& Texture(EAttachmentPoint pAttachment, FRTextureWarp* pTexture)
			{
				mBuilder.texture(static_cast<filament::RenderTarget::AttachmentPoint>(pAttachment), PtrValue(pTexture));
				return *this;
			}

			FRRenderTargetWarp* Build(FREngineWarp* pEngine)
			{
				return new FRRenderTargetWarp(pEngine, this);
			}

		private:
			filament::RenderTarget::Builder mBuilder;
		};

		FRRenderTargetWarp() = default;

		FRRenderTargetWarp(FREngineWarp* pEngine, Builder* mBuilder);

	};
}

