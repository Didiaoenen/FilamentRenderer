#include "GUI.FRButton.h"
#include <MathDefine.h>

FR::GUI::FRButton::FRButton(const std::string& pLabel, const glm::vec2& pSize, bool pDisabled, bool pAlignText)
	: label(pLabel)
	, disabled(pDisabled)
	, alignText(pAlignText)
{
	size = pSize;
	auto& style = ImGui::GetStyle();
	textColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_Text]);
	idleBackgroundColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_Button]);
	clickedBackgroundColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_ButtonActive]);
	hoveredBackgroundColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_ButtonHovered]);
}

void FR::GUI::FRButton::_Draw_Impl()
{
	SetItemLayout();

	auto& style = ImGui::GetStyle();
	auto defaultTextColor = style.Colors[ImGuiCol_Text];
	auto defaultIdleColor = style.Colors[ImGuiCol_Button];
	auto defaultClickedColor = style.Colors[ImGuiCol_ButtonActive];
	auto defaultHoveredColor = style.Colors[ImGuiCol_ButtonHovered];

	style.Colors[ImGuiCol_Text] = MathConvert::ToImVec4(textColor);
	style.Colors[ImGuiCol_Button] = MathConvert::ToImVec4(idleBackgroundColor);
	style.Colors[ImGuiCol_ButtonActive] = MathConvert::ToImVec4(clickedBackgroundColor);
	style.Colors[ImGuiCol_ButtonHovered] = MathConvert::ToImVec4(hoveredBackgroundColor);

	auto flags = 0;
	
	if (disabled)
	{
		flags |= ImGuiItemFlags_Disabled;
	}

	if (alignText)
	{
		flags = flags | ImGuiButtonFlags_AlignTextBaseLine;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { style.FramePadding.x, 0.f });
	}

	if (ImGui::ButtonEx((label + mWidgetID).c_str(), MathConvert::ToImVec2(mCaculeteSize), flags))
	{
		ClickedEvent.Invoke();
	}

	if (alignText)
	{
		ImGui::PopStyleVar();
	}

	style.Colors[ImGuiCol_Text] = defaultTextColor;
	style.Colors[ImGuiCol_Button] = defaultIdleColor;
	style.Colors[ImGuiCol_ButtonActive] = defaultClickedColor;
	style.Colors[ImGuiCol_ButtonHovered] = defaultHoveredColor;
}

FR::GUI::FRButtonArrow::FRButtonArrow(ImGuiDir pDirection)
	: direction(pDirection)
{
}

void FR::GUI::FRButtonArrow::_Draw_Impl()
{
	if (ImGui::ArrowButton(mWidgetID.c_str(), direction))
	{
		ClickedEvent.Invoke();
	}
}

FR::GUI::FRButtonColored::FRButtonColored(const std::string& pLabel, const Color &pColor, const glm::vec2& pSize, bool pEnableAlpha)
	: label(pLabel)
	, color(pColor)
	, enableAlpha(pEnableAlpha)
{
	size = pSize;
}

void FR::GUI::FRButtonColored::_Draw_Impl()
{
	SetItemLayout();

	ImVec4 imColor = MathConvert::ToImVec4(color);
	if (ImGui::ColorButton((label + mWidgetID).c_str(), imColor, !enableAlpha ? ImGuiColorEditFlags_NoAlpha : 0, MathConvert::ToImVec2(size)))
	{
		ClickedEvent.Invoke();
	}

	color = MathConvert::ToGlmVec4(imColor);
}

FR::GUI::FRButtonImage::FRButtonImage(void* pTextureID, const glm::vec2& pSize)
	: textureID(pTextureID)
{
	size = pSize;
}

void FR::GUI::FRButtonImage::_Draw_Impl()
{
	ImVec4 tn = MathConvert::ToImVec4(tint);
	ImVec4 bg = MathConvert::ToImVec4(background);

	if (ImGui::ImageButton(mWidgetID.c_str(), textureID, MathConvert::ToImVec2(size), {0.f, 1.f}, {1.f, 0.f}, bg, tn))
	{
		ClickedEvent.Invoke();
	}
}

FR::GUI::FRButtonSmall::FRButtonSmall(const std::string& pLabel)
	: label(pLabel)
{
	auto& style = ImGui::GetStyle();
	textColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_Text]);
	idleBackgroundColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_Button]);
	clickedBackgroundColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_ButtonActive]);
	hoveredBackgroundColor = MathConvert::ToGlmVec4(style.Colors[ImGuiCol_ButtonHovered]);
}

void FR::GUI::FRButtonSmall::_Draw_Impl()
{
	SetItemLayout();

	auto& style = ImGui::GetStyle();
	auto defaultTextColor = style.Colors[ImGuiCol_Text];
	auto defaultIdleColor = style.Colors[ImGuiCol_Button];
	auto defaultClickedColor = style.Colors[ImGuiCol_ButtonActive];
	auto defaultHoveredColor = style.Colors[ImGuiCol_ButtonHovered];

	style.Colors[ImGuiCol_Text] = MathConvert::ToImVec4(textColor);
	style.Colors[ImGuiCol_Button] = MathConvert::ToImVec4(idleBackgroundColor);
	style.Colors[ImGuiCol_ButtonActive] = MathConvert::ToImVec4(clickedBackgroundColor);
	style.Colors[ImGuiCol_ButtonHovered] = MathConvert::ToImVec4(hoveredBackgroundColor);

	if (ImGui::SmallButton((label + mWidgetID).c_str()))
	{
		ClickedEvent.Invoke();
	}

	style.Colors[ImGuiCol_Text] = defaultTextColor;
	style.Colors[ImGuiCol_Button] = defaultIdleColor;
	style.Colors[ImGuiCol_ButtonActive] = defaultClickedColor;
	style.Colors[ImGuiCol_ButtonHovered] = defaultHoveredColor;
}

FR::GUI::FRButtonInvisible::FRButtonInvisible(const glm::vec2& pSize)
{
	size = pSize;
}

void FR::GUI::FRButtonInvisible::_Draw_Impl()
{
	SetItemLayout();

	const ImVec2 contentAvail = ImGui::GetContentRegionAvail();
	ImGui::InvisibleButton(mWidgetID.c_str(), size != vec2f::zero ? MathConvert::ToImVec2(size) : contentAvail);
}
