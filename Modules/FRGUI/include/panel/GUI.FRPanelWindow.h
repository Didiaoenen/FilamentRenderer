#pragma once

#include <string>
#include <Tools.FREvent.h>
#include "GUI.FRAPanelTrans.h"
#include "GUI.FRPanelWindowSettings.h"

namespace FR::GUI
{
	class FRPanelWindow
		: public FRAPanelTrans
	{
	public:
		FRPanelWindow(const std::string pName = "", bool pOpened = true, const FRPanelWindowSettings& pSetting = {});

		void Open();

		void Close();

		void Focus();

		void SetOpened(bool pValue);

		bool IsOpened();

		bool IsHovered();

		bool IsFocused();

		bool IsAppearing();

		void ScrollToBottom();

		void ScrollToTop();

		bool IsScrolledToBottom();

		bool IsScrolledToTop();

	protected:
		void _Draw_Impl() override;

		virtual void DrawGizmo() {}

	public:
		std::string name{};

		glm::vec2 minSize{ 0.f, 0.f };
		glm::vec2 maxSize{ 0.f, 0.f };

		bool resizable{ true };
		bool closable{ false };
		bool movable{ true };
		bool scrollable{ true };
		bool dockable{ false };
		bool hideBackground{ false };
		bool forceHorizontalScrollbar{ false };
		bool forceVerticalScrollbar{ false };
		bool allowHorizontalScrollbar{ false };
		bool bringToFrontOnFocus{ true };
		bool collapsable{ false };
		bool allowInputs{ true };
		bool titleBar{ true };

		FREvent<> OpenEvent;
		FREvent<> CloseEvent;

	protected:
		bool mOpened{ false };
		bool mHovered{ false };
		bool mFocused{ false };
		bool mMustScrollToTop{ false };
		bool mMustScrollToBottom{ false };
		bool mScrolledToTop{ false };
		bool mScrolledToBottom{ false };
		glm::vec2 mViewportOffset{ 0.0f };

	};
}

