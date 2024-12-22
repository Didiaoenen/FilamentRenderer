#include "Editor.FRAPanelView.h"

#include "Editor.FRInput.h"

#include <Core.FRView.h>
#include <Core.FRScene.h>
#include <Core.FRCamera.h>
#include <Core.FRTexture.h>
#include <Core.FRRenderTarget.h>
#include <Core.FRSceneRenderer.h>

using namespace FR::GUI;

namespace
{
	constexpr float kTitleBarHeight = 22.f;
	constexpr glm::vec2 kViewSize{ 1024.f, 640.f };
}

FR::FRAPanelView::FRAPanelView(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSetting)
	: FRPanelWindow(pTitle, pOpened, pSetting)
{
	scrollable = false;

	mColorTextures.fill(nullptr);
	mDepthTextures.fill(nullptr);
	mRenderTargets.fill(nullptr);

	mView.SetVisibleLayers(0x4, 0x4);

	{
		InitRenderTarget(kViewSize);

		mImage = &CreateWidget<FRImage>(mColorTexture, kViewSize);
	}
}

void FR::FRAPanelView::_Draw_Impl()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	{
		FRPanelWindow::_Draw_Impl();
	}
	ImGui::PopStyleVar();
}

void FR::FRAPanelView::DrawFrame(FRARenderer* pRenderer)
{
	GetScene()->ParseScene();
	GetCamera()->CacheViewMatrix();

	pRenderer->DrawFrame(&mView);

	mRenderFrames++;
}

void FR::FRAPanelView::Update()
{
	mView.SetScene(GetScene());
	mView.SetCamera(GetCamera());

	auto size = GetSafeSize();
	mImageSizeChanged = mImage->size != size;
	if (mImageSizeChanged)
	{
		mImage->size = size;
	}
}

glm::vec2 FR::FRAPanelView::GetSafeSize()
{
	const auto& size = GetSize();
	return { size.x, std::max(0.f, size.y - kTitleBarHeight)};
}

void FR::FRAPanelView::ResizeRenderTarget()
{
	if (mImageSizeChanged && mImage->size != glm::vec2())
	{
		{
			InitRenderTarget(mImage->size);

			mImage->textureID = mColorTexture;
		}

		delete mColorTextures[(mRenderFrames - 1) % 2]; mColorTextures[(mRenderFrames - 1) % 2] = nullptr;
		delete mDepthTextures[(mRenderFrames - 1) % 2]; mDepthTextures[(mRenderFrames - 1) % 2] = nullptr;
		delete mRenderTargets[(mRenderFrames - 1) % 2]; mRenderTargets[(mRenderFrames - 1) % 2] = nullptr;
	}
}

void FR::FRAPanelView::InitRenderTarget(const glm::vec2& pSize)
{
	mColorTexture = mColorTextures[mRenderFrames % 2] = new FRTexture(
		pSize.x, pSize.y, ETexture::EInternalFormat::RGBA8, ETexture::ESampler::SAMPLER_2D, { ETexture::EUsage::COLOR_ATTACHMENT, ETexture::EUsage::SAMPLEABLE });

	mDepthTexture = mDepthTextures[mRenderFrames % 2] = new FRTexture(
		pSize.x, pSize.y, ETexture::EInternalFormat::DEPTH24, ETexture::ESampler::SAMPLER_2D, { ETexture::EUsage::DEPTH_ATTACHMENT });

	mRenderTarget = mRenderTargets[mRenderFrames % 2] = new FRRenderTarget(mColorTexture, mDepthTexture);

	mView.SetRenderTarget(mRenderTarget);

	mView.SetViewport({ 0, 0, pSize.x, pSize.y });

	if (auto camera = mView.GetCamera())
	{
		camera->SetViewport({ 0, 0, pSize.x, pSize.y });
		camera->CalculateProjectionMatrix(pSize.x,  pSize.y);
	}
}
