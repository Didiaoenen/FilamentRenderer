#include "GUI.FRPopup.h"

FR::GUI::FRPopup::FRPopup(const std::string& pName)
	: FRAWidget(pName)
	, name(pName)
{
}

void FR::GUI::FRPopup::OpenPopup()
{
	auto min = ImGui::GetItemRectMin();
	auto max = ImGui::GetItemRectMax();
	ImGui::SetNextWindowPos({ min.x, max.y });
	ImGui::OpenPopup(name.c_str());
}

void FR::GUI::FRPopup::_Draw_Impl()
{
	if (size != glm::vec2{0.f, 0.f})
	{
		ImGui::SetNextWindowSize({ size.x, size.y });
	}

	if (ImGui::BeginPopup(name.c_str()))
	{
		DrawWidgets();
		ImGui::EndPopup();
	}
}
