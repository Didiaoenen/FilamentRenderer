#include "Core.FRView.h"

#include "Core.FRScene.h"
#include "Core.FRCamera.h"
#include "Core.FRRenderTarget.h"

#include <FRViewWarp.h>
#include <FRSceneWarp.h>
#include <FRCameraWarp.h>
#include <FREngineWarp.h>
#include <FRViewportWarp.h>
#include <FRFilamentHelper.h>

FR::FRView::FRView()
{
	mView = FRFilamentHelper::GetEngine()->CreateView();
}

void FR::FRView::SetScene(FRScene* pScene)
{
	mScene = pScene;
	mView->SetScene(pScene->NativePtr());
}

void FR::FRView::SetCamera(FRCamera* pCamera)
{
	mCamera = pCamera;
	mView->SetCamera(pCamera->NativePtr());
}

void FR::FRView::SetViewport(glm::vec4 pViewPort)
{
	mView->SetViewport({
		static_cast<int32_t>(pViewPort.x), static_cast<int32_t>(pViewPort.y),
		static_cast<uint32_t>(pViewPort.z), static_cast<uint32_t>(pViewPort.w) });
}

void FR::FRView::SetRenderTarget(FRRenderTarget* pRenderTarget)
{
	mRenderTarget = pRenderTarget;
	mView->SetRenderTarget(pRenderTarget->NativePtr());
}

void FR::FRView::SetVisibleLayers(uint8_t pSelect, uint8_t pValue)
{
	mView->SetVisibleLayers(pSelect, pValue);
}

void FR::FRView::SetFrustumCullingEnabled(bool bEnabled)
{
	mView->SetFrustumCullingEnabled(bEnabled);
}

void FR::FRView::SetPostProcessingEnabled(bool bEnabled)
{
	mView->SetPostProcessingEnabled(bEnabled);
}

void FR::FRView::SetName(const std::string& pName)
{
	mView->SetName(pName.c_str());
}

const std::string FR::FRView::GetName()
{
	return mView->GetName();
}

FR::FRCamera* FR::FRView::GetCamera()
{
	return mCamera;
}

FR::FRViewWarp* FR::FRView::NativePtr()
{
	return mView;
}

FR::FRView::~FRView()
{
	FRFilamentHelper::GetEngine()->Destroy(mView);
}