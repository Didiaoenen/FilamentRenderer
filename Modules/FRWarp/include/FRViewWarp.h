#pragma once

#include "FRPtrWarp.h"
#include <filament/View.h>

namespace FR
{
	class FRSceneWarp;
	class FREngineWarp;
	class FRCameraWarp;
	class FRViewportWarp;
	class FRRenderTargetWarp;

	class FRViewWarp
		: public FRPtrWarp<filament::View>
	{
	public:
		FRViewWarp() = default;

		FRViewWarp(FREngineWarp* pEngine);
		
		const std::string GetName();

		filament::RenderTarget* GetRenderTarget();

		void SetName(const std::string& pName);

		void SetScene(FRSceneWarp* pScene);

		void SetCamera(FRCameraWarp* pCamera);

		void SetViewport(FRViewportWarp&& pViewport);

		void SetRenderTarget(FRRenderTargetWarp* pRenderTarget);

		void SetVisibleLayers(uint8_t pSelect, uint8_t pValue);

		void SetBlendMode(filament::View::BlendMode pMode);

		void SetShadowingEnabled(bool pEnabled);

		void SetFrustumCullingEnabled(bool bEnabled);

		void SetPostProcessingEnabled(bool pEnabled);

	public:
		~FRViewWarp();

	};
}

