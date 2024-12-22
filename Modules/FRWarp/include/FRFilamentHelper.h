#pragma once

#include <cstdint>

namespace FR
{
	class FREntityWarp;
	class FREntityManagerWarp;

	class FRSceneWarp;
	class FRCameraWarp;
	class FREngineWarp;
	class FRRendererWarp;
	class FRSwapChainWarp;

	class FRLightManagerWarp;
	class FRTransformManagerWarp;
	class FRRenderableManagerWarp;

	class FRFilamentHelper
	{
	public:
		static FREngineWarp* CreateEngine(void* pWindow);

		static FREngineWarp* GetEngine();
		static FRRendererWarp* GetRenderer();
		static FRSwapChainWarp* GetSwapChain();

		static FRLightManagerWarp* GetLightManager();
		static FRTransformManagerWarp* GetTransformManager();
		static FRRenderableManagerWarp* GetRenderableManager();
		static FREntityManagerWarp* GetEntityManager();

		static FRSceneWarp* CreateScene();

		static FRCameraWarp* CreateCamera();

		static FREntityWarp* CreateEntity();

		static void DestroyEngine();

		static void DestroyEntity(FREntityWarp* pEntity);

	private:
		inline static FREngineWarp* mEngine = nullptr;
		inline static FRRendererWarp* mRenderer = nullptr;
		inline static FRSwapChainWarp* mSwapChain = nullptr;

	};
}