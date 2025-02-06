#include "FREngineWarp.h"

#include "FRViewWarp.h"
#include "FRSceneWarp.h"
#include "FRFenceWarp.h"
#include "FRCameraWarp.h"
#include "FRRendererWarp.h"
#include "FRSwapChainWarp.h"

#include "FREntityManagerWarp.h"
#include "FRLightManagerWarp.h"
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
}

FR::FREntityManagerWarp* FR::FREngineWarp::GetEntityManager()
{
	return new FR::FREntityManagerWarp(this);
}

FR::FRRenderableManagerWarp* FR::FREngineWarp::GetRenderableManager()
{
	return new FR::FRRenderableManagerWarp(this);
}

FR::FRLightManagerWarp* FR::FREngineWarp::GetLightManager()
{
	return new FR::FRLightManagerWarp(this);
}

FR::FRTransformManagerWarp* FR::FREngineWarp::GetTransformManager()
{
	return new FR::FRTransformManagerWarp(this);
}

FR::FRSwapChainWarp* FR::FREngineWarp::CreateSwapChain(void* pWindow)
{
	return new FR::FRSwapChainWarp(this, pWindow);
}

FR::FRRendererWarp* FR::FREngineWarp::CreateRenderer()
{
	return new FR::FRRendererWarp(this);
}

FR::FRViewWarp* FR::FREngineWarp::CreateView()
{
	return new FR::FRViewWarp(this);
}

FR::FRSceneWarp* FR::FREngineWarp::CreateScene()
{
	return new FR::FRSceneWarp(this);
}

FR::FRFenceWarp* FR::FREngineWarp::CreateFence()
{
	return new FR::FRFenceWarp(this);
}

FR::FRCameraWarp* FR::FREngineWarp::CreateCamera(FREntityWarp* pEntity)
{
	return new FR::FRCameraWarp(this, pEntity);
}

FR::FRCameraWarp* FR::FREngineWarp::GetCameraComponent(FREntityWarp* pEntity)
{
	return nullptr;
}

void FR::FREngineWarp::DestroyCameraComponent(FREntityWarp* pEntity)
{
	PtrValue(this)->destroyCameraComponent(PtrValue(pEntity));
}

FR::FRJobSystemWarp* FR::FREngineWarp::GetJobSystem()
{
	return nullptr;
}

void FR::FREngineWarp::SetPaused(bool pPaused)
{
}

void FR::FREngineWarp::Flush()
{
}

void FR::FREngineWarp::FlushAndWait()
{
}

bool FR::FREngineWarp::IsPaused()
{
	return false;
}

void FR::FREngineWarp::Execute()
{
}

void FR::FREngineWarp::Destroy()
{
	filament::Engine::destroy(PtrValue(this));
}

void FR::FREngineWarp::Destroy(FREntityWarp* pEntity)
{
	PtrValue(this)->destroy(PtrValue(pEntity));
}
