#pragma once

#include <array>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include <Core.FRView.h>
#include <Core.FRGuiDrawer.h>
#include <GUI.FRPanelWindow.h>

namespace FR
{
	class FRActor;
	class FRScene;
	class FRCamera;
	class FRTexture;
	class FRARenderer;
	class FRRenderTarget;

	class FRAPanelView
		: public GUI::FRPanelWindow
	{
	public:
		FRAPanelView(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSetting);

		virtual void DrawFrame(FRARenderer* pRenderer);

		virtual void _Draw_Impl() override;

		virtual FRScene* GetScene() = 0;

		virtual FRCamera* GetCamera() = 0;

		virtual void Update();

		glm::vec2 GetSafeSize();

		void ResizeRenderTarget();

	protected:
		virtual ~FRAPanelView() = default;

		virtual void InitRenderTarget(const glm::vec2& pSize);

	protected:
		FRView mView;

		uint64_t mRenderFrames{ 0 };

		GUI::FRImage* mImage{ nullptr };
		bool mImageSizeChanged{ false };

		FRActor* mSelectActor{ nullptr };

		FRTexture* mColorTexture{ nullptr };
		FRTexture* mDepthTexture{ nullptr };
		FRRenderTarget* mRenderTarget{ nullptr };
		std::array<FRTexture*, 2> mColorTextures{ nullptr };
		std::array<FRTexture*, 2> mDepthTextures{ nullptr };
		std::array<FRRenderTarget*, 2> mRenderTargets{ nullptr };

	};
}
