#pragma once

#include "FRPtrWarp.h"
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

			FRSkyboxWarp* Build(FREngineWarp* pEngine)
			{

			}

		private:
			filament::Skybox::Builder mBuilder;

		};

		FRSkyboxWarp() = default;

		FRSkyboxWarp(FREngineWarp* pEngine, Builder* pBuilder);

	};
}

