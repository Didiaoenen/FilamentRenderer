#include "FRViewWarp.h"
#include "FRSceneWarp.h"
#include "FREngineWarp.h"
#include "FRCameraWarp.h"
#include "FRViewportWarp.h"
#include "FRRenderTargetWarp.h"

FR::FRViewWarp::FRViewWarp(FREngineWarp* pEngine)
{
	mValue = FRPtrValue(PtrValue(pEngine)->createView());
}

const std::string FR::FRViewWarp::GetName()
{
	return PtrValue(this)->getName();
}

filament::RenderTarget* FR::FRViewWarp::GetRenderTarget()
{
	return PtrValue(this)->getRenderTarget();
}

void FR::FRViewWarp::SetName(const std::string& pName)
{
	PtrValue(this)->setName(pName.c_str());
}

void FR::FRViewWarp::SetScene(FRSceneWarp* pScene)
{
	PtrValue(this)->setScene(PtrValue(pScene));
}

void FR::FRViewWarp::SetCamera(FRCameraWarp* pCamera)
{
	PtrValue(this)->setCamera(PtrValue(pCamera));
}

void FR::FRViewWarp::SetViewport(FRViewportWarp&& pViewport)
{
	PtrValue(this)->setViewport(RefValue(pViewport));
}

void FR::FRViewWarp::SetRenderTarget(FRRenderTargetWarp* pRenderTarget)
{
	PtrValue(this)->setRenderTarget(PtrValue(pRenderTarget));
}

void FR::FRViewWarp::SetVisibleLayers(uint8_t pSelect, uint8_t pValue)
{
	PtrValue(this)->setVisibleLayers(pSelect, pValue);
}

void FR::FRViewWarp::SetBlendMode(filament::View::BlendMode pMode)
{
	PtrValue(this)->setBlendMode(pMode);
}

void FR::FRViewWarp::SetShadowingEnabled(bool pEnabled)
{
	PtrValue(this)->setShadowingEnabled(pEnabled);
}

void FR::FRViewWarp::SetFrustumCullingEnabled(bool bEnabled)
{
	PtrValue(this)->setFrustumCullingEnabled(bEnabled);
}

void FR::FRViewWarp::SetPostProcessingEnabled(bool pEnabled)
{
	PtrValue(this)->setPostProcessingEnabled(pEnabled);
}

FR::FRViewWarp::~FRViewWarp()
{

}
