#pragma once

#include <cstdint>
#include <Tools.FROptRef.h>

namespace FR
{
	class FRCamera;

	struct FRFrameDescriptor
	{
		uint16_t renderWidth = 0;
		uint16_t renderHeight = 0;
		FROptRef<FRCamera> camera;
	};
}