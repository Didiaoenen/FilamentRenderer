#pragma once

#include "FRPtrWarp.h"
#include <filament/Scene.h>

namespace FR
{
	class FREntityWarp;
	class FREngineWarp;
	class FRSkyboxWarp;
	class FRIndirectLightWarp;

	class FRSceneWarp
		: public FRPtrWarp<filament::Scene>
	{
	public:
		FRSceneWarp() = default;

		FRSceneWarp(FREngineWarp* pEngine);

		void AddEntity(FREntityWarp* pEntity);

		void SetSkybox(FRSkyboxWarp* pSkybox);

		void SetIndirectLight(FRIndirectLightWarp* pIndirectLight);

		void Remove(FREntityWarp* pEntity);

	public:
		virtual ~FRSceneWarp();

	};
}

