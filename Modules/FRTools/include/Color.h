#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/color_space.hpp>

namespace FR
{
	struct Color
	{
		Color(glm::vec3 pVector);
		Color(glm::vec4 pVector);
		Color(float pR = 1.f, float pG = 1.f, float pB = 1.f, float pA = 1.f);

		glm::vec3 ToVec3();
		glm::vec4 ToVec4();

		bool operator==(const Color& pOther);

		bool operator!=(const Color& pOther);

		union
		{
			float x;
			float r;
		};

		union
		{
			float y;
			float g;
		};

		union
		{
			float z;
			float b;
		};

		union
		{
			float w;
			float a;
		};

		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;
		static const Color Grey;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;
	};
}

