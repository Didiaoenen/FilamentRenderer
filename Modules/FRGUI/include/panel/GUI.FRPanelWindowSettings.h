#pragma once

namespace FR::GUI
{
	struct FRPanelWindowSettings
	{
		bool closable = false;
		bool resizable = true;
		bool movable = true;
		bool dockable = false;
		bool scrollable = true;
		bool hideBackground = false;
		bool forceHorizontalScrollbar = false;
		bool forceVerticalScrollbar = false;
		bool allowHorizontalScrollbar = false;
		bool bringToFrontOnFocus = true;
		bool collapsable = false;
		bool allowInputs = true;
		bool titleBar = true;
		bool autoSize = false;
	};
}