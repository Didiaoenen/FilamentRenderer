#pragma once

#include "FRPtrWarp.h"
#include "FRTextureWarp.h"
#include <filament/Skybox.h>

namespace FR
{
	class FREngineWarp;

	class FRSkyboxWarp
		: public FRPtrWarp<filament::Skybox>
	{
	public:

		class Builder
		{
			friend class FRSkyboxWarp;

		public:
			Builder()
				: mBuilder()
			{
			}

			Builder& Environment(FRTextureWarp* pCubemap)
			{
				mBuilder.environment(PtrValue(pCubemap));
				return *this;
			}

			Builder& ShowSun(bool pShow)
			{
				mBuilder.showSun(pShow);
				return *this;
			}

			FRSkyboxWarp* Build(FREngineWarp* pEngine)
			{
				return new FRSkyboxWarp(pEngine, this);
			}

		private:
			filament::Skybox::Builder mBuilder;

		};

		FRSkyboxWarp() = default;

		FRSkyboxWarp(FREngineWarp* pEngine, Builder* pBuilder);

	};
}

