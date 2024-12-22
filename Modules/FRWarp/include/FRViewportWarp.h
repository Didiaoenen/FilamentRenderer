#pragma once

#include "FRObjWarp.h"
#include <filament/Viewport.h>

namespace FR
{
	class FRViewportWarp
		: public FRObjWarp<filament::Viewport>
	{
	public:
		FRViewportWarp() = default;

		FRViewportWarp(int32_t pLeft, int32_t pBottom, uint32_t pWidth, uint32_t pHeight);

	};
}

