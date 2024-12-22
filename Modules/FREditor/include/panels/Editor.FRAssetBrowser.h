#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <Core.FRGuiDrawer.h>
#include <GUI.FRPanelWindow.h>

namespace FR
{
	class FRAssetBrowser
		: public GUI::FRPanelWindow
	{
	public:
		FRAssetBrowser(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSettings);

		void Refresh();

	private:
		void ParseFolder(FRWidgetContainer& pRoot, const std::string& pDirectory, bool pIsEngineItem);
		
		void ConsiderItem(FRWidgetContainer* pRoot, const std::string& pDirectory, bool pIsEngineItem, bool pAutoOpen = false);
		
		void RenderItemBody(FRWidgetContainer* pRoot, const std::string& pDirectory, bool pIsEngineItem, bool pAutoOpen = false);

	private:
		int mItemScale{ 55 };

		std::string mEngineFolder;
		std::string mProjectFolder;

		FRWidgetContainer* mAssetList{ nullptr };
		FRWidgetContainer* mAssetView{ nullptr };

		std::unordered_map<GUI::FRAWidget*, std::string> mPathUpdate;

	};
}

