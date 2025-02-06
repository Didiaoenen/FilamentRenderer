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

		FRBoxWarp(const glm::vec3& pCenter, const glm::vec3& pHalfExtent);

	};
}

