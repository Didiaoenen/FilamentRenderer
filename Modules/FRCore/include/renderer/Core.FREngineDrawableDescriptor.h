#pragma once

#include <glm/glm.hpp>

namespace FR
{
	struct FREngineDrawableDescriptor
	{
		glm::mat4 modelMatrix;
		glm::mat4 userMatrix;
	};
}