#pragma once

#include "FRObjWarp.h"
#include <glm/glm.hpp>
#include <filament/Box.h>

namespace FR
{
	class FRBoxWarp
		: public FRObjWarp<filament::Box>
	{
	public:
		FRBoxWarp() = default;

		FRBoxWarp(glm::vec3 pCenter, glm::vec3 pHalfExtent);

	};
}

