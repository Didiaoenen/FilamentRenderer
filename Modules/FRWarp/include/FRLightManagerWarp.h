#pragma once

#include "FRRefWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"

#include <Color.h>
#include <glm/glm.hpp>
#include <filament/LightManager.h>

namespace FR
{
	class FRLightManagerWarp
		: public FRRefWarp<filament::LightManager>
	{
	public:
		using EType = filament::LightManager::Type;

		static constexpr float C_EFFICIENCY_LED = filament::LightManager::EFFICIENCY_LED;

	public:
		class Builder
		{
			friend class FRLightManagerWarp;

		public:
			using EResult = filament::LightManager::Builder::Result;

		public:
			Builder(EType pType)
				: mBuilder(pType)
			{
			}

			EResult Build(FREngineWarp* pEngine, FREntityWarp* pEntity)
			{
				return mBuilder.build(*PtrValue(pEngine), PtrValue(pEntity));
			}

		private:
			filament::LightManager::Builder mBuilder;

		};

		class Instance
		{
		public:
			Instance() = default;

			Instance(FRLightManagerWarp* pLightManager, FREntityWarp* pEntity)
				: mIns(PtrValue(pLightManager).getInstance(PtrValue(pEntity)))
			{
			}

			filament::LightManager::Instance Ins()
			{
				return mIns;
			}

		private:
			filament::LightManager::Instance mIns;

		};

		FRLightManagerWarp() = default;

		FRLightManagerWarp(FREngineWarp* pEngine);

		void SetPosition(Instance pInstance, const glm::vec3& pPosition);

		void SetDirection(Instance pInstance, const glm::vec3& pDirection);

		void SetColor(Instance pInstance, const Color& pColor);

		void SetFalloff(Instance pInstance, float pRadius);
		
		void SetIntensity(Instance pInstance, float pIntensity);

		void SetIntensity(Instance pInstance, float pIntensity, float pEfficiency);

		void SetIntensityCandela(Instance pInstance, float pIntensity);

		void SetShadowCaster(Instance pInstance, bool pShadowCaster);
		
		void SetSpotLightCone(Instance pInstance, float pInner, float pOuter);

		void SetSunAngularRadius(Instance pInstance, bool pSunAngular);

		Instance GetInstance(FREntityWarp* pEntity);

		void Destroy(FREntityWarp* pEntity);

	};
}

