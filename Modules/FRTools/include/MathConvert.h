#pragma once

#include "Color.h"

#include <imgui.h>

#include <glm/glm.hpp>  
#include <glm/gtc/quaternion.hpp>

#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/quat.h>
#include <filament/Color.h>

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/maths/soa_transform.h>

namespace FR
{
	class MathConvert
	{
	public:
		/**
		 * vec2
		*/
		static ImVec2 ToImVec2(const glm::vec2& pValue);

		static glm::vec2 ToGlmVec2(const ImVec2& pValue);

		static filament::math::float2 ToFVec2(const glm::vec2& pValue);

		static glm::vec2 ToGlmVec2(const filament::math::float2& pValue);

		/**
		 * vec3
		*/
		static filament::math::float3 ToFVec3(const glm::vec3& pValue);

		static filament::LinearColor ToFColor(const Color& pValue);

		static glm::vec3 ToGlmVec3(const filament::math::float3& pValue);

		/**
		 * vec4
		*/
		static ImVec4 ToImVec4(const Color& pValue);

		static glm::vec4 ToGlmVec4(const ImVec4& pValue);

		static filament::math::float4 ToFVec4(const glm::vec4& pValue);

		static filament::LinearColorA ToFColorA(const Color& pValue);

		static glm::vec4 ToGlmVec4(const filament::math::float4& pValue);

		/**
		 * mat4
		*/
		static ozz::math::Float4x4 ToOzzMat4(const glm::mat4& pValue);

		static filament::math::mat4f ToFMat4(const glm::mat4& pValue);

		static glm::mat4 ToGlmMat4(const ozz::math::Float4x4& pValue);

		static glm::mat4 ToGlmMat4(const filament::math::mat4& pValue);

		/**
		 * quat4
		*/
		static filament::math::quat ToFQuat(const glm::quat& pValue);

		static glm::quat ToGlmQuat(const filament::math::quat& pValue);
	};
}

