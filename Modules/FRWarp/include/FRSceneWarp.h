#pragma once

#include "FRPtrWarp.h"
#include <filament/Scene.h>

namespace FR
{
	class FREntityWarp;
	class FRSkyboxWarp;
	class FREngineWarp;

	class FRSceneWarp
		: public FRPtrWarp<filament::Scene>
	{
	public:
		FRSceneWarp() = default;

		FRSceneWarp(FREngineWarp* pEngine);

		void AddEntity(FREntityWarp* pEntity);

		void SetSkybox(filament::Skybox* pSkybox);

		void SetIndirectLight(filament::IndirectLight* ibl);

		void Remove(FREntityWarp* pEntity);

	};
}

