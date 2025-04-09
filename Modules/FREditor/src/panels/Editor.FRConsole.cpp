#include "Editor.FRConsole.h"
#include "Editor.FRImGuiHelper.h"

#include <Tools.FRMessage.h>

#include <IconsMaterialDesignIcons.h>

using namespace FR::GUI;

namespace FR
{
	std::pair<const char*, Color> GetRenderIcon(FRILogHandler::ELogLevel level)
	{
		switch (level)
		{
		case FRILogHandler::ELogLevel::LOG_INFO:
			return { ICON_MDI_INFORMATION, { 0.40f, 0.70f, 1.00f } };
		case FRILogHandler::ELogLevel::LOG_WARN:
			return { ICON_MDI_ALERT, { 1.00f, 1.00f, 0.00f } };
		case FRILogHandler::ELogLevel::LOG_TRACE:
			return { ICON_MDI_MESSAGE_TEXT, { 0.75f, 0.75f, 0.75f } };
		case FRILogHandler::ELogLevel::LOG_DEBUG:
			return { ICON_MDI_BUG, { 0.00f, 0.50f, 0.50f } };
		case FRILogHandler::ELogLevel::LOG_ERROR:
			return { ICON_MDI_CLOSE_OCTAGON, { 1.00f, 0.25f, 0.25f } };
		case FRILogHandler::ELogLevel::LOG_CRITICAL:
			return { ICON_MDI_ALERT_OCTAGRAM, { 0.6f, 0.2f, 0.8f } };
		}
		return { "", {} };
	}

	std::tuple<const char*, Color, std::string> GetWidgetSettingsFromLogData(const FRILogHandler::LogData& pLogData)
	{
		auto renderIcon = GetRenderIcon(pLogData.logLevel);
		std::string logDateFormated = " [" + pLogData.date + "]";
		return { renderIcon.first, renderIcon.second, logDateFormated };
	}
}

FR::FRLogBar::FRLogBar()
{
	auto& groupLayer = CreateWidget<FRGroup>();
	auto tracyIcon = GetRenderIcon(FRILogHandler::ELogLevel::LOG_TRACE);

	auto infoIcon = GetRenderIcon(FRILogHandler::ELogLevel::LOG_INFO);
	mInfoBtn = &groupLayer.CreateWidget<FRButton>(infoIcon.first);
	{
		mInfoBtn->textColor = infoIcon.second;
		mInfoBtn->lineBreak = false;

		mInfoBtn->ClickedEvent += [this, infoIcon]()
			{
				mInfoClicked = !mInfoClicked;
				mInfoBtn->textColor = mInfoClicked ? Color{ 0.5f, 0.5, 0.5f } : infoIcon.second;
				dynamic_cast<FRConsole*>(parent)->SetShowInfoLogs(!mInfoClicked);
			};
	}

	auto warnIcon = GetRenderIcon(FRILogHandler::ELogLevel::LOG_WARN);
	mWarnBtn = &groupLayer.CreateWidget<FRButton>(warnIcon.first);
	{
		mWarnBtn->textColor = warnIcon.second;
		mWarnBtn->lineBreak = false;

		mWarnBtn->ClickedEvent += [this, warnIcon]()
			{
				mWarnClicked = !mWarnClicked;
				mWarnBtn->textColor = mWarnClicked ? Color{ 0.5f, 0.5, 0.5f } : warnIcon.second;
				dynamic_cast<FRConsole*>(parent)->SetShowWarnLogs(!mWarnClicked);
			};
	}

	mTraceBtn = &groupLayer.CreateWidget<FRButton>(tracyIcon.first);
	{
		mTraceBtn->textColor = tracyIcon.second;
		mTraceBtn->lineBreak = false;

		mTraceBtn->ClickedEvent += [this, tracyIcon]()
			{
				mTraceClicked = !mTraceClicked;
				mTraceBtn->textColor = mTraceClicked ? Color{ 0.5f, 0.5, 0.5f } : tracyIcon.second;
				dynamic_cast<FRConsole*>(parent)->SetShowTraceLogs(!mTraceClicked);
			};
	}

	auto debugIcon = GetRenderIcon(FRILogHandler::ELogLevel::LOG_DEBUG);
	mDebugBtn = &groupLayer.CreateWidget<FRButton>(debugIcon.first);
	{
		mDebugBtn->textColor = debugIcon.second;
		mDebugBtn->lineBreak = false;

		mDebugBtn->ClickedEvent += [this, debugIcon]()
			{
				mDebugClicked = !mDebugClicked;
				mDebugBtn->textColor = mDebugClicked ? Color{ 0.5f, 0.5, 0.5f } : debugIcon.second;
				dynamic_cast<FRConsole*>(parent)->SetShowDebugLogs(!mDebugClicked);
			};
	}

	auto errorIcon = GetRenderIcon(FRILogHandler::ELogLevel::LOG_ERROR);
	mErrorBtn = &groupLayer.CreateWidget<FRButton>(errorIcon.first);
	{
		mErrorBtn->textColor = errorIcon.second;
		mErrorBtn->lineBreak = false;

		mErrorBtn->ClickedEvent += [this, errorIcon]()
			{
				mErrorClicked = !mErrorClicked;
				mErrorBtn->textColor = mErrorClicked ? Color{ 0.5f, 0.5, 0.5f } : errorIcon.second;
				dynamic_cast<FRConsole*>(parent)->SetShowErrorLogs(!mErrorClicked);
			};
	}

	auto criticalIcon = GetRenderIcon(FRILogHandler::ELogLevel::LOG_CRITICAL);
	mCriticalBtn = &groupLayer.CreateWidget<FRButton>(criticalIcon.first);
	{
		mCriticalBtn->textColor = criticalIcon.second;

		mCriticalBtn->ClickedEvent += [this, criticalIcon]()
			{
				mCriticalClicked = !mCriticalClicked;
				mCriticalBtn->textColor = mCriticalClicked ? Color{ 0.5f, 0.5, 0.5f } : criticalIcon.second;
				dynamic_cast<FRConsole*>(parent)->SetShowCriticalLogs(!mCriticalClicked);
			};
	}
}

void FR::FRLogBar::_Draw_Impl()
{
	auto& style = ImGui::GetStyle();
	glm::vec2 framePadding = MathConvert::ToGlmVec2(style.FramePadding);
	glm::vec2 totalSize = FRImGuiHelper::GetIconFontSize() * 7.f + framePadding * 7.f;

	glm::vec2 windowSize = MathConvert::ToGlmVec2(ImGui::GetWindowContentRegionMax());
	ImGui::SetCursorPosX(windowSize.x - totalSize.x);

	DrawWidgets();
}

FR::FRConsole::FRConsole(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRPanelWindow(ICON_MDI_VIEW_LIST " " + pTitle, pOpened, pSettings)
{
	auto& clearButton = CreateWidget<FRButton>("Clear");
	{
		clearButton.idleBackgroundColor = { 0.5f, 0.f, 0.f };
		clearButton.ClickedEvent += std::bind(&FRConsole::Clear, this);
		clearButton.lineBreak = false;
	}

	auto& clearOnPlay = CreateWidget<FRCheckBox>(mClearOnPlay, "Auto Clear On Play");
	{
		clearOnPlay.ValueChangedEvent += [this](bool pValue) { mClearOnPlay = pValue; };
		clearOnPlay.alignment = EWidgetAlignment::LEFT;
		clearOnPlay.lineBreak = false;
	}

	CreateWidget<FRLogBar>();

	CreateWidget<FRSeparator>();

	mLogGroup = &CreateWidget<FRGroup>();

	//EDITOR_EVENT(PlayEvent) += std::bind(&FRConsole::ClearOnPlay, this);

	FRMessage::AddListener<FRConsole, FRILogHandler::LogData>(MessageType::LOG, this, &FRConsole::OnLogIntercepted);
}

void FR::FRConsole::OnLogIntercepted(FRILogHandler::LogData pLogData)
{
	auto [logIcon, logColor, logDate] = GetWidgetSettingsFromLogData(pLogData);

	auto& consoleItem1 = mLogGroup->CreateWidget<FRTextColored>(logIcon + logDate + pLogData.message, logColor);
	{
		consoleItem1.enabled = IsAllowedByFilter(pLogData.logLevel);
		mLogTextWidgets[&consoleItem1] = pLogData.logLevel;
	}

	//mLogGroup->CreateWidget<TableView>();
}

void FR::FRConsole::ClearOnPlay()
{
	if (mClearOnPlay)
	{
		Clear();
	}
}

void FR::FRConsole::Clear()
{
	mLogTextWidgets.clear();
	mLogGroup->RemoveAllWidgets();
}

void FR::FRConsole::FilterLogs()
{
	for (const auto& [widget, logLevel] : mLogTextWidgets)
	{
		widget->enabled = IsAllowedByFilter(logLevel);
	}
}

bool FR::FRConsole::IsAllowedByFilter(FRILogHandler::ELogLevel pLogLevel)
{
	switch (pLogLevel)
	{
	case FRILogHandler::ELogLevel::LOG_INFO:
		return mShowInfoLog;
	case FRILogHandler::ELogLevel::LOG_WARN:
		return mShowWarnLog;
	case FRILogHandler::ELogLevel::LOG_TRACE:
		return mShowTraceLog;
	case FRILogHandler::ELogLevel::LOG_DEBUG:
		return mShowDebugLog;
	case FRILogHandler::ELogLevel::LOG_ERROR:
		return mShowErrorLog;
	case FRILogHandler::ELogLevel::LOG_CRITICAL:
		return mShowCriticalLog;
	}
	return false;
}

void FR::FRConsole::SetShowTraceLogs(bool pValue)
{
	mShowTraceLog = pValue;
	FilterLogs();
}

void FR::FRConsole::SetShowDebugLogs(bool pValue)
{
	mShowDebugLog = pValue;
	FilterLogs();
}

void FR::FRConsole::SetShowInfoLogs(bool pValue)
{
	mShowInfoLog = pValue;
	FilterLogs();
}

void FR::FRConsole::SetShowWarnLogs(bool pValue)
{
	mShowWarnLog = pValue;
	FilterLogs();
}

void FR::FRConsole::SetShowErrorLogs(bool pValue)
{
	mShowErrorLog = pValue;
	FilterLogs();
}

void FR::FRConsole::SetShowCriticalLogs(bool pValue)
{
	mShowCriticalLog = pValue;
	FilterLogs();
}
