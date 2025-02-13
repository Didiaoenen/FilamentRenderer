#include "FREngineWarp.h"

#include "FRViewWarp.h"
#include "FRSceneWarp.h"
#include "FRFenceWarp.h"
#include "FRCameraWarp.h"
#include "FRSkyboxWarp.h"
#include "FRRendererWarp.h"
#include "FRSwapChainWarp.h"

#include "FRJobSystemWarp.h"

#include "FRLightManagerWarp.h"
#include "FREntityManagerWarp.h"
#include "FRTransformManagerWarp.h"
#include "FRRenderableManagerWarp.h"

FR::FREngineWarp::FREngineWarp()
{
	filament::Engine::Config engineConfig;
	engineConfig.stereoscopicEyeCount = 2;
	engineConfig.stereoscopicType = filament::Engine::StereoscopicType::INSTANCED;

	auto engine = filament::Engine::Builder()
		.backend(filament::Engine::Backend::DEFAULT)
		.featureLevel(filament::backend::FeatureLevel::FEATURE_LEVEL_3)
		.config(&engineConfig)
		.build();

	mValue = FRPtrValue(engine);

	mEntityManager = new FREntityManagerWarp(this);

	mRenderableManager = new FRRenderableManagerWarp(this);

	mLightManager = new FRLightManagerWarp(this);

	mTransformManager = new FRTransformManagerWarp(this);

	mJobSystem = new FRJobSystemWarp(this);
}

FR::FRJobSystemWarp* FR::FREngineWarp::GetJobSystem()
{
	return mJobSystem;
}

FR::FREntityManagerWarp* FR::FREngineWarp::GetEntityManager()
{
	return mEntityManager;
}

FR::FRRenderableManagerWarp* FR::FREngineWarp::GetRenderableManager()
{
	return mRenderableManager;
}

FR::FRLightManagerWarp* FR::FREngineWarp::GetLightManager()
{
	return mLightManager;
}

FR::FRTransformManagerWarp* FR::FREngineWarp::GetTransformManager()
{
	return mTransformManager;
}

FR::FRSwapChainWarp* FR::FREngineWarp::CreateSwapChain(void* pWindow)
{
	auto swapChain = new FRSwapChainWarp(this, pWindow);
	mSwapChains.emplace_back(swapChain);
	return swapChain;
}

FR::FRRendererWarp* FR::FREngineWarp::CreateRenderer()
{
	auto renderer = new FRRendererWarp(this);
	mRenderers.emplace_back(renderer);
	return renderer;
}

FR::FRViewWarp* FR::FREngineWarp::CreateView()
{
	auto view = new FRViewWarp(this);
	mViews.emplace_back(view);
	return view;
}

FR::FRSceneWarp* FR::FREngineWarp::CreateScene()
{
	auto scene = new FRSceneWarp(this);
	mScenes.emplace_back(scene);
	return scene;
}

FR::FRFenceWarp* FR::FREngineWarp::CreateFence()
{
	auto fence = new FRFenceWarp(this);
	mFences.emplace_back(fence);
	return fence;
}

FR::FRCameraWarp* FR::FREngineWarp::CreateCamera(FREntityWarp* pEntity)
{
	auto camera = new FRCameraWarp(this, pEntity);
	mCameras.emplace_back(camera);
	return camera;
}

void FR::FREngineWarp::RegisterRenderer(FRRendererWarp* pRenderer)
{
	mRenderers.emplace_back(pRenderer);
}

void FR::FREngineWarp::RegisterScene(FRSceneWarp* pScene)
{
	mScenes.emplace_back(pScene);
}

void FR::FREngineWarp::RegisterCamera(FRCameraWarp* pCamera)
{
	mCameras.emplace_back(pCamera);
}

void FR::FREngineWarp::RegisterSkybox(FRSkyboxWarp* pSkybox)
{
	mSkyboxes.emplace_back(pSkybox);
}

void FR::FREngineWarp::RegisterTexture(FRTextureWarp* pTexture)
{
	mTextures.emplace_back(pTexture);
}

void FR::FREngineWarp::RegisterIndexBuffer(FRIndexBufferWarp* pIndexBuffer)
{
	mIndexBuffers.emplace_back(pIndexBuffer);
}

void FR::FREngineWarp::RegisterVertexBuffer(FRVertexBufferWarp* pVertexBuffer)
{
	mVertexBuffers.emplace_back(pVertexBuffer);
}

void FR::FREngineWarp::RegisterRenderTarget(FRRenderTargetWarp* pRenderTarget)
{
	mRenderTargets.emplace_back(pRenderTarget);
}

void FR::FREngineWarp::RegisterSknningBuffer(FRSkinningBufferWarp* pSkinningBuffer)
{
	mSkinningBuffers.emplace_back(pSkinningBuffer);
}

void FR::FREngineWarp::RegisterIndirectLight(FRIndirectLightWarp* pIndirectLight)
{
	mIndirectLights.emplace_back(pIndirectLight);
}

void FR::FREngineWarp::SetPaused(bool pPaused)
{
	PtrValue(this)->setPaused(pPaused);
}

bool FR::FREngineWarp::IsPaused()
{
	return PtrValue(this)->isPaused();
}

void FR::FREngineWarp::Flush()
{
	PtrValue(this)->flush();
}

void FR::FREngineWarp::FlushAndWait()
{
	PtrValue(this)->flushAndWait();
}

void FR::FREngineWarp::Destroy()
{
	for (const auto& vertexBuffer : mVertexBuffers)
	{
		Destroy(vertexBuffer);
	}
	mVertexBuffers.clear();

	for (const auto& indexBuffer : mIndexBuffers)
	{
		Destroy(indexBuffer);
	}
	mIndexBuffers.clear();

	for (const auto& renderTarget : mRenderTargets)
	{
		Destroy(renderTarget);
	}
	mRenderTargets.clear();

	for (const auto& texture : mTextures)
	{
		Destroy(texture);
	}
	mTextures.clear();

	filament::Engine::destroy(PtrValue(this));
}

void FR::FREngineWarp::Destroy(FREntityWarp* pEntity)
{
	PtrValue(this)->destroy(PtrValue(pEntity));
}

FR::FREngineWarp::~FREngineWarp()
{

}
