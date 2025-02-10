#pragma once

#include "FRPtrWarp.h"
#include "FRTextureWarp.h"
#include <filament/IndirectLight.h>

namespace FR
{
	class FREngineWarp;

	class FRIndirectLightWarp
		: FRPtrWarp<filament::IndirectLight>
	{
	public:

		class Builder
		{
			friend class FRIndirectLightWarp;

		public:
			Builder()
				: mBuilder()
			{

			}

			Builder& Reflections(FRTextureWarp* pCubemap)
			{
				mBuilder.reflections(PtrValue(pCubemap));
				return *this;
			}

			Builder& Intensity(float pIntensity)
			{
				mBuilder.intensity(pIntensity);
				return *this;
			}

			FRIndirectLightWarp* Build(FREngineWarp* pEngine)
			{
				return new FRIndirectLightWarp(pEngine, this);
			}

		private:
			filament::IndirectLight::Builder mBuilder;

		};

		FRIndirectLightWarp(FREngineWarp* pEngine, Builder* pBuilder);

	private:

	};
}

