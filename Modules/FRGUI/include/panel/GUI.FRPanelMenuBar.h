#pragma once

#include "GUI.FRAPanel.h"

namespace FR::GUI
{
	class FRPanelMenuBar
		: public FRAPanel
	{
	protected:
		void _Draw_Impl() override;

	};
}

