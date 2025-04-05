#pragma once

#include "GUI.FRIPlugin.h"
#include "GUI.FRWidgetContainer.h"

#include <imgui.h>

namespace FR::GUI
{
	class FRContextualMenu
		: public FRWidgetContainer, public FRIPlugin
	{
	public:
		void Execute();

		void Close();

	};
}

