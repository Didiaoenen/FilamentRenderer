#pragma once

#include <tuple>
#include <Core.FRGuiDrawer.h>
#include <Log.FRILogHandler.h>
#include <GUI.FRPanelWindow.h>
#include <GUI.FRPanelMenuBar.h>

namespace FR
{
	class FRLogBar
		: public GUI::FRAWidget, public GUI::FRPanelMenuBar
	{
	public:
		FRLogBar();

	protected:
		void _Draw_Impl() override;

	protected:
		GUI::FRButton* mInfoBtn{ nullptr };
		GUI::FRButton* mWarnBtn{ nullptr };
		GUI::FRButton* mTraceBtn{ nullptr };
		GUI::FRButton* mDebugBtn{ nullptr };
		GUI::FRButton* mErrorBtn{ nullptr };
		GUI::FRButton* mCriticalBtn{ nullptr };

		bool mInfoClicked{ false };
		bool mWarnClicked{ false };
		bool mTraceClicked{ false };
		bool mDebugClicked{ false };
		bool mErrorClicked{ false };
		bool mCriticalClicked{ false };
	};

	class FRConsole
		: public GUI::FRPanelWindow
	{
		friend class FRLogBar;

	public:
		FRConsole(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSettings);

		void OnLogIntercepted(FRILogHandler::LogData pLogData);

		void ClearOnPlay();

		void Clear();

		void FilterLogs();

		bool IsAllowedByFilter(FRILogHandler::ELogLevel pLogLevel);

	private:
		void SetShowInfoLogs(bool pValue);
		void SetShowWarnLogs(bool pValue);
		void SetShowTraceLogs(bool pValue);
		void SetShowDebugLogs(bool pValue);
		void SetShowErrorLogs(bool pValue);
		void SetShowCriticalLogs(bool pValue);

	private:
		GUI::FRGroup* mLogGroup{ nullptr };
		std::unordered_map<GUI::FRText*, FRILogHandler::ELogLevel> mLogTextWidgets;

		bool mClearOnPlay = true;
		bool mShowInfoLog = true;
		bool mShowWarnLog = true;
		bool mShowTraceLog = true;
		bool mShowDebugLog = true;
		bool mShowErrorLog = true;
		bool mShowCriticalLog = true;

	};
}

