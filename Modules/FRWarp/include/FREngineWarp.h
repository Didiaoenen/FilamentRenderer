#pragma once

#include "FRPtrWarp.h"
#include "FRRendererWarp.h"
#include "FRSwapChainWarp.h"
#include <filament/Engine.h>

#include <vector>

namespace FR
{
	class FREntityWarp;
	class FREntityManagerWarp;
	class FRJobSystemWarp;

	class FRViewWarp;
	class FRFenceWarp;
	class FRSceneWarp;
	class FRCameraWarp;
	class FRSkyboxWarp;
	class FRTextureWarp;
	class FRMaterialWarp;
	class FRRendererWarp;
	class FRSwapChainWarp;
	class FRIndexBufferWarp;
	class FRVertexBufferWarp;
	class FRRenderTargetWarp;
	class FRSkinningBufferWarp;
	class FRIndirectLightWarp;

	class FRLightManagerWarp;
	class FRTransformManagerWarp;
	class FRRenderableManagerWarp;

	class FREngineWarp
		: public FRPtrWarp<filament::Engine>
	{
	public:
		FREngineWarp();

		FRJobSystemWarp* GetJobSystem();

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

		void RegisterRenderer(FRRendererWarp* pRenderer);

		void RegisterScene(FRSceneWarp* pScene);

		void RegisterCamera(FRCameraWarp* pCamera);

		void RegisterSkybox(FRSkyboxWarp* pSkybox);

		void RegisterTexture(FRTextureWarp* pTexture);

		void RegisterIndexBuffer(FRIndexBufferWarp* pIndexBuffer);

		void UnRegisterIndexBuffer(FRIndexBufferWarp* pIndexBuffer);

		void RegisterVertexBuffer(FRVertexBufferWarp* pVertexBuffer);

		void UnRegisterVertexBuffer(FRVertexBufferWarp* pVertexBuffer);

		void RegisterRenderTarget(FRRenderTargetWarp* pRenderTarget);

		void RegisterSknningBuffer(FRSkinningBufferWarp* pSkinningBuffer);

		void UnRegisterSknningBuffer(FRSkinningBufferWarp* pSkinningBuffer);

		void RegisterIndirectLight(FRIndirectLightWarp* pIndirectLight);

		void SetPaused(bool pPaused);

		bool IsPaused();

		void Flush();

		void FlushAndWait();

		void Destroy();

		void Destroy(FREntityWarp* pEntity);

		template<typename T>
		void Destroy(T* pWarpValue);

	public:
		~FREngineWarp();

	private:
		FREntityManagerWarp* mEntityManager{ nullptr };

		FRRenderableManagerWarp* mRenderableManager{ nullptr };

		FRLightManagerWarp* mLightManager{ nullptr };

		FRTransformManagerWarp* mTransformManager{ nullptr };

		FRJobSystemWarp* mJobSystem{ nullptr };

		std::vector<FRSwapChainWarp*> mSwapChains;

		std::vector<FRRendererWarp*> mRenderers;

		std::vector<FRViewWarp*> mViews;

		std::vector<FRSceneWarp*> mScenes;

		std::vector<FRFenceWarp*> mFences;

		std::vector<FRCameraWarp*> mCameras;

		std::vector<FRSkyboxWarp*> mSkyboxes;

		std::vector<FRTextureWarp*> mTextures;

		std::vector<FRIndexBufferWarp*> mIndexBuffers;

		std::vector<FRVertexBufferWarp*> mVertexBuffers;

		std::vector<FRRenderTargetWarp*> mRenderTargets;

		std::vector<FRSkinningBufferWarp*> mSkinningBuffers;

		std::vector<FRIndirectLightWarp*> mIndirectLights;

	};
}

#include "FREngineWarp.inl"
