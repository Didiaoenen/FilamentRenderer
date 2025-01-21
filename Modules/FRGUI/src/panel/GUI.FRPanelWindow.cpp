#include "GUI.FRPanelWindow.h"

#include <MathConvert.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <IconsMaterialDesignIcons.h>

FR::GUI::FRPanelWindow::FRPanelWindow(const std::string& pName, bool pOpened, const FRPanelWindowSettings& pSetting)
	: name(pName)
	, mOpened(pOpened)
	, resizable(pSetting.resizable)
	, closable(pSetting.closable)
	, movable(pSetting.movable)
	, scrollable(pSetting.scrollable)
	, dockable(pSetting.dockable)
	, hideBackground(pSetting.hideBackground)
	, forceHorizontalScrollbar(pSetting.forceHorizontalScrollbar)
	, forceVerticalScrollbar(pSetting.forceVerticalScrollbar)
	, allowHorizontalScrollbar(pSetting.allowHorizontalScrollbar)
	, bringToFrontOnFocus(pSetting.bringToFrontOnFocus)
	, collapsable(pSetting.collapsable)
	, allowInputs(pSetting.allowInputs)
{
	autoSize = pSetting.autoSize;
}

void FR::GUI::FRPanelWindow::Open()
{
	if (!mOpened)
	{
		mOpened = true;
		OpenEvent.Invoke();
	}
}

void FR::GUI::FRPanelWindow::Close()
{
	if (mOpened)
	{
		mOpened = false;
		CloseEvent.Invoke();
	}
}

void FR::GUI::FRPanelWindow::Focus()
{
	ImGui::SetWindowFocus((name + mPanelID).c_str());
}

bool FR::GUI::FRPanelWindow::IsOpened()
{
	return mOpened;
}

bool FR::GUI::FRPanelWindow::IsHovered()
{
	return mHovered;
}

bool FR::GUI::FRPanelWindow::IsFocused()
{
	return mFocused;
}

bool FR::GUI::FRPanelWindow::IsAppearing()
{
	if (auto window = ImGui::FindWindowByName((name + GetPanelID()).c_str()); window)
	{
		return window->Appearing;
	}
	return false;
}

void FR::GUI::FRPanelWindow::ScrollToTop()
{
	mMustScrollToTop = true;
}

void FR::GUI::FRPanelWindow::ScrollToBottom()
{
	mMustScrollToBottom = true;
}

bool FR::GUI::FRPanelWindow::IsScrolledToTop()
{
	return mMustScrollToTop;
}

bool FR::GUI::FRPanelWindow::IsScrolledToBottom()
{
	return mMustScrollToBottom;
}

void FR::GUI::FRPanelWindow::SetOpenState(bool pValue)
{
	if (pValue != mOpened)
	{
		mOpened = pValue;

		if (mOpened)
		{
			OpenEvent.Invoke();
		}
		else
		{
			CloseEvent.Invoke();
		}
	}
}

void FR::GUI::FRPanelWindow::_Draw_Impl()
{
	if (mOpened)
	{
		int windowFlags = ImGuiWindowFlags_None;

		if (!resizable)					windowFlags |= ImGuiWindowFlags_NoResize;
		if (!movable)					windowFlags |= ImGuiWindowFlags_NoMove;
		if (!dockable)					windowFlags |= ImGuiWindowFlags_NoDocking;
		if (hideBackground)				windowFlags |= ImGuiWindowFlags_NoBackground;
		if (forceHorizontalScrollbar)	windowFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
		if (forceVerticalScrollbar)		windowFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
		if (allowHorizontalScrollbar)	windowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
		if (!bringToFrontOnFocus)		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		if (!collapsable)				windowFlags |= ImGuiWindowFlags_NoCollapse;
		if (!allowInputs)				windowFlags |= ImGuiWindowFlags_NoInputs;
		if (!scrollable)				windowFlags |= ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
		if (!titleBar)					windowFlags |= ImGuiWindowFlags_NoTitleBar;

		ImVec2 minSizeConstraint = MathConvert::ToImVec2(minSize);
		ImVec2 maxSizeConstraint = MathConvert::ToImVec2(maxSize);

		/* Cancel constraint if x or y is <= 0.f */
		if (minSizeConstraint.x <= 0.f || minSizeConstraint.y <= 0.f)
		{
			minSizeConstraint = { 0.0f, 0.0f };
		}

		if (maxSizeConstraint.x <= 0.f || maxSizeConstraint.y <= 0.f)
		{
			maxSizeConstraint = { 10000.f, 10000.f };
		}

		ImGui::SetNextWindowSizeConstraints(minSizeConstraint, maxSizeConstraint);

		if (ImGui::Begin((name + mPanelID).c_str(), closable ? &mOpened : nullptr, windowFlags))
		{
			mViewportOffset = MathConvert::ToGlmVec2(ImGui::GetCursorPos());

			mHovered = ImGui::IsWindowHovered();
			mFocused = ImGui::IsWindowFocused();

			mScrolledToTop = ImGui::GetScrollY() == 0.0f;
			mScrolledToBottom = ImGui::GetScrollY() == ImGui::GetScrollMaxY();

			Update();

			if (mMustScrollToTop)
			{
				ImGui::SetScrollY(0.0f);
				mMustScrollToTop = false;
			}

			if (mMustScrollToBottom)
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
				mMustScrollToBottom = false;
			}

			DrawWidgets();

			//
			DrawGizmo();
		}

		ImGui::End();
	}
}
