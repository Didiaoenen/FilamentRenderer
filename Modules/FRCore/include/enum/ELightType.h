#pragma once

#include <filament/LightManager.h>

namespace FR
{
	enum class ELightType : uint8_t
	{
		SUN,            //!< Directional light that also draws a sun's disk in the sky.
		DIRECTIONAL,    //!< Directional light, emits light in a given direction.
		POINT,          //!< Point light, emits light from a position, in all directions.
		FOCUSED_SPOT,   //!< Physically correct spot light.
		SPOT,           //!< Spot light with coupling of outer cone and illumination disabled.
	};

	static filament::LightManager::Type ConvertEnum(ELightType pLightType)
	{
		return static_cast<filament::LightManager::Type>(pLightType);
	}
}