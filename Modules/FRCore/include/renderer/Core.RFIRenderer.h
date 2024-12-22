#pragma once

#include "Core.FRFrameDescriptor.h"

namespace FR
{
	class RFIRenderer
	{
	public:
		virtual bool BeginFrame(const FRFrameDescriptor& pFrameDescriptor) = 0;
		//virtual void DrawFrame() = 0;
		virtual void EndFrame() = 0;
	};
}