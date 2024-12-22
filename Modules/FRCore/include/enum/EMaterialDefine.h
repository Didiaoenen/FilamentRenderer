#pragma once

#include <filament/MaterialInstance.h>

namespace FR
{
	enum class ETransparencyMode : uint8_t
	{
		//! the transparent object is drawn honoring the raster state
		DEFAULT,
		/**
		 * the transparent object is first drawn in the depth buffer,
		 * then in the color buffer, honoring the culling mode, but ignoring the depth test function
		 */
		TWO_PASSES_ONE_SIDE,

		/**
		 * the transparent object is drawn twice in the color buffer,
		 * first with back faces only, then with front faces; the culling
		 * mode is ignored. Can be combined with two-sided lighting
		 */
		TWO_PASSES_TWO_SIDES
	};

	static filament::MaterialInstance::TransparencyMode ConvertEnum(ETransparencyMode pTransparencyMode)
	{
		return static_cast<filament::MaterialInstance::TransparencyMode>(pTransparencyMode);
	}

	enum class ECullingMode : uint8_t
	{
		NONE,               //!< No culling, front and back faces are visible
		FRONT,              //!< Front face culling, only back faces are visible
		BACK,               //!< Back face culling, only front faces are visible
		FRONT_AND_BACK      //!< Front and Back, geometry is not visible
	};

	static filament::MaterialInstance::CullingMode ConvertEnum(ECullingMode pCullingMode)
	{
		return static_cast<filament::MaterialInstance::CullingMode>(pCullingMode);
	}
}