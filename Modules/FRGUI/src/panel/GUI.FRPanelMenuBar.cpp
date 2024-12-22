#include "GUI.FRPanelMenuBar.h"

#include <imgui.h>

void FR::GUI::FRPanelMenuBar::_Draw_Impl()
{
	if (!mWidgets.empty() && ImGui::BeginMainMenuBar())
	{
		DrawWidgets();
		ImGui::EndMainMenuBar();
	}
}
