#include "GUI.FRContextualMenu.h"

void FR::GUI::FRContextualMenu::Execute()
{
	if (ImGui::BeginPopupContextItem())
	{
		DrawWidgets();
		ImGui::EndPopup();
	}
}

void FR::GUI::FRContextualMenu::Close()
{
	ImGui::CloseCurrentPopup();
}
