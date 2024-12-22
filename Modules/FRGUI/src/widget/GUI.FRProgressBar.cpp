#include "GUI.FRProgressBar.h"

FR::GUI::FRProgressBar::FRProgressBar(float pFraction, const glm::vec2& pSize, const std::string& pOverlay)
	: fraction(pFraction)
	, overlay(pOverlay)
{
	size = pSize;
}

void FR::GUI::FRProgressBar::_Draw_Impl()
{
	ImGui::ProgressBar(fraction, MathConvert::ToImVec2(size), !overlay.empty() ? overlay.c_str() : nullptr);
}
