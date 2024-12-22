#include "GUI.FRPanelUndecorated.h"

#include <imgui.h>

void FR::GUI::FRPanelUndecorated::_Draw_Impl()
{
	auto& style = ImGui::GetStyle();
	ImVec2 previousPadding = style.WindowPadding;
	ImVec2 previousMinSize = style.WindowMinSize;
	style.WindowPadding = { 0, 0 };
	style.WindowMinSize = { 0, 0 };

	if (ImGui::Begin(mPanelID.c_str(), nullptr, CollectFlags()))
	{
		style.WindowPadding = previousPadding;
		style.WindowMinSize = previousMinSize;

		Update();

		DrawWidgets();

		ImGui::End();
	}
	else
	{
		style.WindowPadding = previousPadding;
	}
}

int FR::GUI::FRPanelUndecorated::CollectFlags()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysUseWindowPadding |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoBackground;

	return autoSize ? flags |= ImGuiWindowFlags_AlwaysAutoResize : flags;
}
