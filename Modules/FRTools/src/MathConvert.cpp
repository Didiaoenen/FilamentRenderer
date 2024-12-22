#include "MathConvert.h"

namespace FR
{
	#define VEC2(value) {(value).x, (value).y}
	#define VEC3(value) {(value).x, (value).y, (value).z}
	#define VEC4(value) {(value).x, (value).y, (value).z, (value).w}
	#define QUAT(value) {(float)(value).x, (float)(value).y, (float)(value).z, (float)(value).w}
}

ImVec2 FR::MathConvert::ToImVec2(const glm::vec2& pValue)
{
	return VEC2(pValue);
}

glm::vec2 FR::MathConvert::ToGlmVec2(const ImVec2& pValue)
{
	return VEC2(pValue);
}

filament::math::float2 FR::MathConvert::ToFVec2(const glm::vec2& pValue)
{
	return VEC2(pValue);
}

glm::vec2 FR::MathConvert::ToGlmVec2(const filament::math::float2& pValue)
{
	return VEC2(pValue);
}

filament::math::float3 FR::MathConvert::ToFVec3(const glm::vec3& pValue)
{
	return VEC3(pValue);
}

filament::LinearColor FR::MathConvert::ToFColor(const Color& pValue)
{
	return VEC3(pValue);
}

glm::vec3 FR::MathConvert::ToGlmVec3(const filament::math::float3& pValue)
{
	return VEC3(pValue);
}

ImVec4 FR::MathConvert::ToImVec4(const Color& pValue)
{
	return VEC4(pValue);
}

glm::vec4 FR::MathConvert::ToGlmVec4(const ImVec4& pValue)
{
	return VEC4(pValue);
}

filament::math::float4 FR::MathConvert::ToFVec4(const glm::vec4& pValue)
{
	return VEC4(pValue);
}

filament::LinearColorA FR::MathConvert::ToFColorA(const Color& pValue)
{
	return VEC4(pValue);
}

glm::vec4 FR::MathConvert::ToGlmVec4(const filament::math::float4& pValue)
{
	return VEC4(pValue);
}

ozz::math::Float4x4 FR::MathConvert::ToOzzMat4(const glm::mat4& pValue)
{
	ozz::math::Float4x4 mat4;
	for (size_t i = 0; i < 4; i++)
	{
		mat4.cols[i].m128_f32[0] = pValue[i].x;
		mat4.cols[i].m128_f32[1] = pValue[i].y;
		mat4.cols[i].m128_f32[2] = pValue[i].z;
		mat4.cols[i].m128_f32[3] = pValue[i].w;
	}
	return mat4;
}

filament::math::mat4 FR::MathConvert::ToFMat4(const glm::mat4& pValue)
{
	filament::math::mat4 mat4;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat4[i][j] = pValue[i][j];
		}
	}
	return mat4;
}

glm::mat4 FR::MathConvert::ToGlmMat4(const ozz::math::Float4x4& pValue)
{
	glm::mat4 mat4(1.0);
	for (size_t i = 0; i < 4; i++)
	{
		mat4[i].x = pValue.cols[i].m128_f32[0];
		mat4[i].y = pValue.cols[i].m128_f32[1];
		mat4[i].z = pValue.cols[i].m128_f32[2];
		mat4[i].w = pValue.cols[i].m128_f32[3];
	}
	return mat4;
}

glm::mat4 FR::MathConvert::ToGlmMat4(const filament::math::mat4& pValue)
{
	glm::mat4 mat4(1.0);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat4[i][j] = pValue[i][j];
		}
	}
	return mat4;
}

filament::math::quat FR::MathConvert::ToFQuat(const glm::quat& pValue)
{
	return QUAT(pValue);
}

glm::quat FR::MathConvert::ToGlmQuat(const filament::math::quat& pValue)
{
	return QUAT(pValue);
}