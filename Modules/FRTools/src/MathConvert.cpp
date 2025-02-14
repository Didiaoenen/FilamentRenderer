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
	mat4.cols[0].m128_f32[0] = pValue[0].x; mat4.cols[0].m128_f32[1] = pValue[0].y; mat4.cols[0].m128_f32[2] = pValue[0].z; mat4.cols[0].m128_f32[3] = pValue[0].w;
	mat4.cols[1].m128_f32[0] = pValue[1].x; mat4.cols[1].m128_f32[1] = pValue[1].y; mat4.cols[1].m128_f32[2] = pValue[1].z; mat4.cols[1].m128_f32[3] = pValue[1].w;
	mat4.cols[2].m128_f32[0] = pValue[2].x; mat4.cols[2].m128_f32[1] = pValue[2].y; mat4.cols[2].m128_f32[2] = pValue[2].z; mat4.cols[2].m128_f32[3] = pValue[2].w;
	mat4.cols[3].m128_f32[0] = pValue[3].x; mat4.cols[3].m128_f32[1] = pValue[3].y; mat4.cols[3].m128_f32[2] = pValue[3].z; mat4.cols[3].m128_f32[3] = pValue[3].w;
	return mat4;
}

filament::math::mat4f FR::MathConvert::ToFMat4(const glm::mat4& pValue)
{
	return filament::math::mat4f(
		pValue[0][0], pValue[0][1], pValue[0][2], pValue[0][3],
		pValue[1][0], pValue[1][1], pValue[1][2], pValue[1][3], 
		pValue[2][0], pValue[2][1], pValue[2][2], pValue[2][3], 
		pValue[3][0], pValue[3][1], pValue[3][2], pValue[3][3]);
}

glm::mat4 FR::MathConvert::ToGlmMat4(const ozz::math::Float4x4& pValue)
{
	glm::mat4 mat4(1.0);
	mat4[0].x = pValue.cols[0].m128_f32[0]; mat4[0].y = pValue.cols[0].m128_f32[1]; mat4[0].z = pValue.cols[0].m128_f32[2]; mat4[0].w = pValue.cols[0].m128_f32[3];
	mat4[1].x = pValue.cols[1].m128_f32[0]; mat4[1].y = pValue.cols[1].m128_f32[1]; mat4[1].z = pValue.cols[1].m128_f32[2]; mat4[1].w = pValue.cols[1].m128_f32[3];
	mat4[2].x = pValue.cols[2].m128_f32[0]; mat4[2].y = pValue.cols[2].m128_f32[1]; mat4[2].z = pValue.cols[2].m128_f32[2]; mat4[2].w = pValue.cols[2].m128_f32[3];
	mat4[3].x = pValue.cols[3].m128_f32[0]; mat4[3].y = pValue.cols[3].m128_f32[1]; mat4[3].z = pValue.cols[3].m128_f32[2]; mat4[3].w = pValue.cols[3].m128_f32[3];
	return mat4;
}

glm::mat4 FR::MathConvert::ToGlmMat4(const filament::math::mat4& pValue)
{
	return glm::mat4(
		pValue[0][0], pValue[0][1], pValue[0][2], pValue[0][3],
		pValue[1][0], pValue[1][1], pValue[1][2], pValue[1][3],
		pValue[2][0], pValue[2][1], pValue[2][2], pValue[2][3],
		pValue[3][0], pValue[3][1], pValue[3][2], pValue[3][3]);
}

filament::math::quat FR::MathConvert::ToFQuat(const glm::quat& pValue)
{
	return QUAT(pValue);
}

glm::quat FR::MathConvert::ToGlmQuat(const filament::math::quat& pValue)
{
	return QUAT(pValue);
}