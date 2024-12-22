#pragma once

#include <string>
#include <unordered_map>
#include <Core.FRGuiDrawer.h>
#include <GUI.FRPanelWindow.h>
#include <GUI.FRPanelMenuBar.h>

namespace FR
{
	class FRMenuBar
		: public GUI::FRAWidget, public GUI::FRWidgetContainer
	{
	public:
		FRMenuBar();

	protected:
		void _Draw_Impl() override;

	protected:
		GUI::FRButton* mPlayButton{ nullptr };
		GUI::FRButton* mPauseButton{ nullptr };
		GUI::FRButton* mForwardButton{ nullptr };

	};

	class FRToolBar
		: public GUI::FRPanelMenuBar
	{
	public:
		FRToolBar();

	private:
		void CreateFileMenu();
		void CreateActorsMenu();
		void CreateSettingsMenu();
		void CreateLayoutMenu();
		void CreateHelpMenu();

	};
}

