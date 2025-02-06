#pragma once

#include "FRPtrWarp.h"
#include "FRRendererWarp.h"
#include "FRSwapChainWarp.h"
#include <filament/Engine.h>

namespace FR
{
	class FREntityWarp;
	class FREntityManagerWarp;
	class FRJobSystemWarp;

	class FRViewWarp;
	class FRFenceWarp;
	class FRSceneWarp;
	class FRCameraWarp;
	class FRRendererWarp;
	class FRSwapChainWarp;

	class FRLightManagerWarp;
	class FRTransformManagerWarp;
	class FRRenderableManagerWarp;

	class FREngineWarp
		: public FRPtrWarp<filament::Engine>
	{
	public:
		FREngineWarp();

		FREntityManagerWarp* GetEntityManager();

		FRRenderableManagerWarp* GetRenderableManager();

		FRLightManagerWarp* GetLightManager();

		FRTransformManagerWarp* GetTransformManager();

		FRSwapChainWarp* CreateSwapChain(void* pWindow);

		FRRendererWarp* CreateRenderer();

		FRViewWarp* CreateView();

		FRSceneWarp* CreateScene();

		FRFenceWarp* CreateFence();

		FRCameraWarp* CreateCamera(FREntityWarp* pEntity);

		FRCameraWarp* GetCameraComponent(FREntityWarp* pEntity);

		void DestroyCameraComponent(FREntityWarp* pEntity);

		FRJobSystemWarp* GetJobSystem();

		void SetPaused(bool pPaused);

		void Flush();

		void FlushAndWait();

		void Execute();

		bool IsPaused();

		void Destroy();

		void Destroy(FREntityWarp* pEntity);

		template<typename T>
		inline void Destroy(T* pPtr)
		{
			if (pPtr)
			{
				PtrValue(this)->destroy(PtrValue(pPtr));
			}
		}
	};
}

#include "FREngineWarp.inl"
