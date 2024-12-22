#pragma once

#include "Core.FRARenderFeature.h"

namespace FR
{
	struct FRDrawable;

	class FRCompositeRenderer;

	class EngineBufferRenderFeature
		: public ARenderFeature
	{
	public:
		EngineBufferRenderFeature(FRCompositeRenderer& pRenderer);

	protected:
		virtual void OnBeginFrame() override;
		virtual void OnEndFrame() override;

		virtual void OnBeforeDraw(const FRDrawable& pDrawable) override;

	public:
		~EngineBufferRenderFeature() = default;

	};
}