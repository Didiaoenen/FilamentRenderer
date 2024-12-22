#pragma once

#include <string>
#include <Core.FRCamera.h>
#include <Core.FRGuiDrawer.h>
#include "Editor.FRAPanelView.h"
#include "Editor.FRCameraController.h"

namespace FR
{
	class FRAViewController
		: public FRAPanelView
	{
	public:
		FRAViewController(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSetting);

		virtual void Update() override;

		virtual void InitRenderTarget(const glm::vec2& pSize) override;

		virtual void ResetCameraTransform();

		virtual FRCamera* GetCamera();

		FRCameraController& GetCameraController();

	public:
		~FRAViewController() = default;

	protected:
		FRCameraController mCameraController;

	};
}

