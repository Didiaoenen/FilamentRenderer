#include "GUI.FRFileItem.h"
#include "GUI.FRImage.h"
#include "GUI.FRButton.h"
#include <Core.FRTexture2D.h>
#include <ImguiTextClipped.h>

FR::GUI::FRFileItem::FRFileItem(const std::string& pName, const glm::vec2& pSize,
	bool pDirectory, int pScalePercent, FRTexture2D* pBackgroud, FRTexture2D* pThumbnail, FRTexture2D* pColorFrame)
	: name(pName)
	, directory(pDirectory)
	, scalePercent(pScalePercent)
	, backgroud(pBackgroud)
	, thumbnail(pThumbnail)
	, colorFrame(pColorFrame)
{
	size = pSize;
}

void FR::GUI::FRFileItem::_Draw_Impl()
{
	auto& style = ImGui::GetStyle();
	auto fontSize = ImGui::GetFontSize();
	auto itemSize = size * (scalePercent / 100.0f);

	float padding = 3.0f;
	glm::vec2 backgroudSize = itemSize - padding * 2;
	glm::vec2 thumbnailSize = { itemSize.x - padding * 4, itemSize.y * 0.45f };
	glm::vec2 colorFrameSize = { itemSize.x - padding * 4, 2.0f };

	auto cursorPos = ImGui::GetCursorPos();
	ImGui::ButtonEx(mWidgetID.c_str(), MathConvert::ToImVec2(itemSize), ImGuiButtonFlags_None);

	ImGui::SetItemAllowOverlap();
	ImGui::SetCursorPos({ cursorPos.x + padding, cursorPos.y + padding });
	ImGui::Image(backgroud->NativePtr(), MathConvert::ToImVec2(backgroudSize), { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 56.0f / 255.0f, 56.0f / 255.0f, 56.0f / 255.0f, 255 / 255.0f });

	ImGui::SetItemAllowOverlap();
	ImGui::SetCursorPos({ cursorPos.x + padding * 2, cursorPos.y + padding * 2 });
	ImGui::Image(thumbnail->NativePtr(), MathConvert::ToImVec2(thumbnailSize), { 0.0f, 0.0f }, { 1.0f, 1.0f });

	ImGui::SetItemAllowOverlap();
	ImGui::SetCursorPos({ cursorPos.x + padding * 2, cursorPos.y + thumbnailSize.y + padding * 2 + 4.0f });
	ImGui::Image(colorFrame->NativePtr(), MathConvert::ToImVec2(colorFrameSize), { 0.0f, 0.0f }, { 1.0f, 1.0f });

	ImGui::SetItemAllowOverlap();
	const ImVec2 rectMin = ImGui::GetItemRectMin();
	const ImVec2 rectSize = ImGui::GetItemRectSize();
	const ImVec2 min = { rectMin.x + padding, rectMin.y + padding };
	const ImVec2 max = { rectMin.x + rectSize.x, rectMin.y + fontSize * 2 + padding };
	ImGui::TextClipped(name.c_str(), min, max, nullptr, nullptr, { 0.0f, 0.0f }, nullptr, max.x - min.x);

	ImGui::SetItemAllowOverlap();
	ImGui::SetCursorPos(cursorPos);
	ImGui::InvisibleButton((name + mWidgetID).c_str(), MathConvert::ToImVec2(itemSize));
}
