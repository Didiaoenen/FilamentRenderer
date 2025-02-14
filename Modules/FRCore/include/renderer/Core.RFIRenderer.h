#pragma once

#include "Core.FRFrameDescriptor.h"

namespace FR
{
	class FRView;

	class RFIRenderer
	{
	public:
		virtual bool BeginFrame(const FRFrameDescriptor& pFrameDescriptor) = 0;
		virtual void DrawFrame(FRView* pView) = 0;
		virtual void EndFrame() = 0;
	};
}