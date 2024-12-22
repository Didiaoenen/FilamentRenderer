#pragma once

#include <imgui.h>
#include "GUI.FRIPlugin.h"
#include "GUI.FRWidgetContainer.h"

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

