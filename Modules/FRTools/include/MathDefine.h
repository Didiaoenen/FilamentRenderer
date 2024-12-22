#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace FR
{

#define Zero2 { 0.f, 0.f }
#define Zero3 { 0.f, 0.f, 0.f }
#define Zero4 { 0.f, 0.f, 0.f, 0.f }

#define One2 { 1.f, 1.f }
#define One3 { 1.f, 1.f, 1.f }
#define One4 { 1.f, 1.f, 1.f, 1.f }

	namespace vec2f
	{
		static const glm::vec2 zero(0.f, 0.f);
	}

	namespace vec3f
	{
		static const glm::vec3 zero(0.f, 0.f, 0.f);
		static const glm::vec3 one(1.f, 1.f, 1.f);
		static const glm::vec3 forward(0.f, 0.f, 1.f);
		static const glm::vec3 right(1.f, 0.f, 0.f);
		static const glm::vec3 up(0.f, 1.f, 0.f);
	}

	namespace vec4f
	{
		static const glm::vec4 zero(0.f, 0.f, 0.f, 0.f);
	}

	namespace mat4
	{
		static const glm::mat4 identity(1.f);
	}

	namespace quat
	{
		static const glm::quat identity(0.f, 0.f, 0.f, 1.f);
	}
}