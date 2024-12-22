#include "Editor.FRToolBar.h"

#include "Editor.FRImGuiHelper.h"
#include "Editor.FREditorActions.h"

#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

FR::FRMenuBar::FRMenuBar()
{
	auto& groupLayer = CreateWidget<FRGroup>();
	mPlayButton = &groupLayer.CreateWidget<FRButton>(ICON_MDI_PLAY);
	{
		mPlayButton->alignText = true;
		mPlayButton->lineBreak = false;
		mPlayButton->ClickedEvent += std::bind(&FREditorActions::Playing, &GetService(FREditorActions));
	}
	
	mPauseButton = &groupLayer.CreateWidget<FRButton>(ICON_MDI_PAUSE);
	{
		mPauseButton->alignText = true;
		mPauseButton->lineBreak = false;
		mPauseButton->ClickedEvent += std::bind(&FREditorActions::Pause, &GetService(FREditorActions));
	}

	mForwardButton = &groupLayer.CreateWidget<FRButton>(ICON_MDI_STEP_FORWARD);
	{
		mForwardButton->alignText = true;
		mForwardButton->lineBreak = false;
		mForwardButton->ClickedEvent += std::bind(&FREditorActions::NextFrame, &GetService(FREditorActions));
	}

	GetService(FREditorActions).EditorModeChangedEvent += [this](FREditorActions::EEditorMode pNewMode)
		{
			auto enable = [](FRButton* pButton, bool pEnable)
				{
					pButton->disabled = !pEnable;
					pButton->textColor = pEnable ? Color{ 1.0f, 1.0f, 1.0f, 1.0f } : Color{ 0.5f, 0.5, 0.5f, 0.5f };
				};

			switch (pNewMode)
			{
			case FREditorActions::EEditorMode::EDIT:
			{
				enable(mPlayButton, true);
				enable(mPauseButton, false);
				enable(mForwardButton, false);
			}
				break;
			case FREditorActions::EEditorMode::PLAY:
			{
				enable(mPlayButton, false);
				enable(mPauseButton, true);
				enable(mForwardButton, true);
			}
				break;
			case FREditorActions::EEditorMode::PAUSE:
			{
				enable(mPlayButton, true);
				enable(mPauseButton, false);
				enable(mForwardButton, true);
			}
				break;
			case FREditorActions::EEditorMode::FRAME_BY_FRAME:
			{
				enable(mPlayButton, true);
				enable(mPauseButton, false);
				enable(mForwardButton, true);
			}
				break;
			}
		};

	GetService(FREditorActions).SetCurrentEditorMode(FREditorActions::EEditorMode::EDIT);
}

void FR::FRMenuBar::_Draw_Impl()
{
	auto style = ImGui::GetStyle();
	glm::vec2 framePadding = MathConvert::ToGlmVec2(style.FramePadding);
	glm::vec2 totalSize = FRImGuiHelper::GetIconFontSize() * 3.f + framePadding * 2.f;
	
	glm::vec2 windowSize = MathConvert::ToGlmVec2(ImGui::GetWindowContentRegionMax());
	ImGui::SetCursorPos({ windowSize.x * 0.5f - totalSize.x * 0.5f, 0.f });

	DrawWidgets();
}

FR::FRToolBar::FRToolBar()
{
	CreateFileMenu();
	CreateActorsMenu();
	CreateSettingsMenu();
	CreateLayoutMenu();
	CreateHelpMenu();

	CreateWidget<FRMenuBar>();
}

void FR::FRToolBar::CreateFileMenu()
{
	auto& fileMenu = CreateWidget<FRMenuList>("File");
}

void FR::FRToolBar::CreateActorsMenu()
{
	auto& actorsMenu = CreateWidget<FRMenuList>("Actors");
}

void FR::FRToolBar::CreateSettingsMenu()
{
	auto& settingsMenu = CreateWidget<FRMenuList>("Settings");
}

void FR::FRToolBar::CreateLayoutMenu()
{
	auto& layoutMenu = CreateWidget<FRMenuList>("Layout");
}

void FR::FRToolBar::CreateHelpMenu()
{
	auto& helpMenu = CreateWidget<FRMenuList>("Help");
}
