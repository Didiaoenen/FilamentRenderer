#include "Color.h"

namespace FR
{
	const Color Color::Red     = { 1.0f, 0.0f, 0.0f };
	const Color Color::Green   = { 0.0f, 1.0f, 0.0f };
	const Color Color::Blue    = { 0.0f, 0.0f, 1.0f };
	const Color Color::White   = { 1.0f, 1.0f, 1.0f };
	const Color Color::Black   = { 0.0f, 0.0f, 0.0f };
	const Color Color::Grey    = { 0.5f, 0.5f, 0.5f };
	const Color Color::Yellow  = { 1.0f, 1.0f, 0.0f };
	const Color Color::Cyan    = { 0.0f, 1.0f, 1.0f };
	const Color Color::Magenta = { 1.0f, 0.0f, 1.0f };
}

FR::Color::Color(float pR, float pG, float pB, float pA)
	: r(pR)
	, g(pG)
	, b(pB)
	, a(pA)
{
}

FR::Color::Color(glm::vec3 pVector)
	: Color(pVector.x, pVector.y, pVector.z)
{
}

FR::Color::Color(glm::vec4 pVector)
	: Color(pVector.x, pVector.y, pVector.z, pVector.w)
{
}

glm::vec3 FR::Color::ToVec3()
{
	return { r, g, b };
}


glm::vec4 FR::Color::ToVec4()
{
	return { r, g, b, a };
}


bool FR::Color::operator==(const Color& pOther)
{
	return false;
}

bool FR::Color::operator!=(const Color& pOther)
{
	return false;
}
