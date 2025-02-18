#include "FRFilamentHelper.h"

#include "FREngineWarp.h"
#include "FREntityManagerWarp.h"

FR::FREngineWarp* FR::FRFilamentHelper::CreateEngine(void* pWindow)
{
	if (!mEngine)
	{
		mEngine = new FREngineWarp();
		mRenderer = mEngine->CreateRenderer();
		mSwapChain = mEngine->CreateSwapChain(pWindow);
	}
	return mEngine;
}

FR::FREngineWarp* FR::FRFilamentHelper::GetEngine()
{
	return mEngine;
}

FR::FRRendererWarp* FR::FRFilamentHelper::GetRenderer()
{
	return mRenderer;
}

FR::FRSwapChainWarp* FR::FRFilamentHelper::GetSwapChain()
{
	return mSwapChain;
}

FR::FRLightManagerWarp* FR::FRFilamentHelper::GetLightManager()
{
	return GetEngine()->GetLightManager();
}

FR::FRTransformManagerWarp* FR::FRFilamentHelper::GetTransformManager()
{
    return GetEngine()->GetTransformManager();
}

FR::FRRenderableManagerWarp* FR::FRFilamentHelper::GetRenderableManager()
{
    return GetEngine()->GetRenderableManager();
}

FR::FREntityManagerWarp* FR::FRFilamentHelper::GetEntityManager()
{
    return GetEngine()->GetEntityManager();
}

FR::FRSceneWarp* FR::FRFilamentHelper::CreateScene()
{
	return GetEngine()->CreateScene();
}

FR::FRCameraWarp* FR::FRFilamentHelper::CreateCamera(FREntityWarp* pEntity)
{
	return GetEngine()->CreateCamera(pEntity);
}

FR::FREntityWarp* FR::FRFilamentHelper::CreateEntity()
{
	return GetEntityManager()->Create();
}

void FR::FRFilamentHelper::DestroyEngine()
{
	GetEngine()->Destroy(mSwapChain);
	delete mSwapChain; mSwapChain = nullptr;

	GetEngine()->Destroy(mRenderer);
	delete mRenderer; mRenderer = nullptr;
	
	GetEngine()->Destroy();
	delete mEngine; mEngine = nullptr;
}

void FR::FRFilamentHelper::DestroyEntity(FREntityWarp* pEntity)
{
	if (pEntity)
	{
		GetEngine()->Destroy(pEntity);
		GetEntityManager()->Destroy(pEntity);
	}
}
