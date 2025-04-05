#pragma once

namespace FR::GUI
{
	struct FRPanelWindowSettings
	{
		bool movable = true;
		bool dockable = false;
		bool closable = false;
		bool resizable = true;
		bool scrollable = true;
		bool hideBackground = false;
		bool allowHorizontalScrollbar = false;
		bool forceHorizontalScrollbar = false;
		bool forceVerticalScrollbar = false;
		bool bringToFrontOnFocus = true;
		bool collapsable = false;
		bool allowInputs = true;
		bool titleBar = true;
		bool autoSize = false;
	};
}