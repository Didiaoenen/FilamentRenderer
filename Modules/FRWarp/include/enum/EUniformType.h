#pragma once

#include <backend/DriverEnums.h>

namespace FR
{
	enum class EUniformType : uint8_t
	{
		BOOL,
		BOOL2,
		BOOL3,
		BOOL4,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		INT,
		INT2,
		INT3,
		INT4,
		UINT,
		UINT2,
		UINT3,
		UINT4,
		MAT3,   //!< a 3x3 float matrix
		MAT4,   //!< a 4x4 float matrix
		STRUCT
	};

	enum class ESamplerType : uint8_t
	{
		SAMPLER_2D,             //!< 2D texture
		SAMPLER_2D_ARRAY,       //!< 2D array texture
		SAMPLER_CUBEMAP,        //!< Cube map texture
		SAMPLER_EXTERNAL,       //!< External texture
		SAMPLER_3D,             //!< 3D texture
		SAMPLER_CUBEMAP_ARRAY,  //!< Cube map array texture (feature level 2)
	};

	enum class ESubpassType : uint8_t
	{
		SUBPASS_INPUT
	};
}