#include "GUI.FRItemSelect.h"
#include "GUI.FRLayout.h"
#include "GUI.FRButton.h"
#include "GUI.FRText.h"
#include <ImguiTextClipped.h>

FR::GUI::FRItemSelect::FRItemSelect(EItemType pType, const std::string& pText, glm::vec2 pPosition)
	: mContext(pText)
	, mItemType(pType)
	, mPosition(pPosition)
{
	position = pPosition;
}

FR::GUI::FRText* FR::GUI::FRItemSelect::GetText()
{
	return mText;
}

void FR::GUI::FRItemSelect::SetText(const std::string& content)
{
	mContext = content;
}

void FR::GUI::FRItemSelect::SetTextReceivedEvent(std::function<void(std::string& pContext, std::pair<std::string, FRGroup*>)> pEvent)
{
	mDataReceivedEvent += [this, pEvent](auto pReceivedData)
		{
			pEvent(mContext, pReceivedData);
		};
}

const char* FR::GUI::FRItemSelect::GetItemIcon(EItemType pType)
{
	switch (pType)
	{
	case FR::GUI::FRItemSelect::EItemType::MODEL:
		return ICON_MDI_GRID;
	case FR::GUI::FRItemSelect::EItemType::SHADER:
		return ICON_MDI_FILE_CODE;
	case FR::GUI::FRItemSelect::EItemType::MATERIAL:
		return ICON_MDI_CIRCLE_OPACITY;
	case FR::GUI::FRItemSelect::EItemType::SKELETON:
		return ICON_MDI_HUMAN;
	case FR::GUI::FRItemSelect::EItemType::ANIMATION:
		return ICON_MDI_PLAY_CIRCLE;
	default:
		break;
	}
	return "";
}

void FR::GUI::FRItemSelect::_Draw_Impl()
{
	auto iconSize = glm::vec2{ 24.f, 22.f };

	// Background
	size = { 1.f, 0.f };
	position = mPosition;
	sizeType = EWidgetSize::RELATIVE;
	alignment = EWidgetAlignment::LEFT;

	SetItemLayout();

	auto& style = ImGui::GetStyle();
	auto defaultIdleColor = style.Colors[ImGuiCol_Button];
	auto defaultClickedColor = style.Colors[ImGuiCol_ButtonActive];
	auto defaultHoveredColor = style.Colors[ImGuiCol_ButtonHovered];

	style.Colors[ImGuiCol_Button] = { 0.0f, 0.0f, 0.0f, 1.0f };
	style.Colors[ImGuiCol_ButtonActive] = { 0.0f, 0.0f, 0.0f, 1.0f };
	style.Colors[ImGuiCol_ButtonHovered] = { 0.0f, 0.0f, 0.0f, 1.0f };

	auto itemSize = CaculateSize();
	ImGui::ButtonEx(mWidgetID.c_str(), MathConvert::ToImVec2(itemSize), ImGuiButtonFlags_None);

	style.Colors[ImGuiCol_Button] = defaultIdleColor;
	style.Colors[ImGuiCol_ButtonActive] = defaultClickedColor;
	style.Colors[ImGuiCol_ButtonHovered] = defaultHoveredColor;

	const ImVec2 rectMin = ImGui::GetItemRectMin();
	const ImVec2 rectMax = ImGui::GetItemRectMax();

	if (ImGui::BeginDragDropTarget())
	{
		ImGuiDragDropFlags targetFlags = ImGuiDragDropFlags_None;
		//targetFlags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;

		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("File", targetFlags))
		{
			auto data = *static_cast<std::pair<std::string, FRGroup*>*>(payload->Data);
			mDataReceivedEvent.Invoke(data);
		}

		ImGui::EndDragDropTarget();
	}

	DrawItemActivityOutline(MathConvert::ToGlmVec2(rectMin), MathConvert::ToGlmVec2(rectMax));

	ImGui::SameLine();
	
	// Icon
	position.x += 3.f;

	SetItemLayout();

	ImGui::SetItemAllowOverlap();
	ImGui::TextColored(MathConvert::ToImVec4({ 127 / 255.0f, 214 / 255.0f, 252 / 255.0f }), GetItemIcon(mItemType));
	ImGui::SameLine();

	// Name
	SetItemLayout();

	ImGui::SetItemAllowOverlap();
	static ImVec2 offset(iconSize.x, 2.f);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec4 clipRect(rectMin.x, rectMin.y, rectMax.x - iconSize.x, rectMax.y);
	const ImVec2 textPos = ImVec2(rectMin.x + offset.x, rectMin.y + offset.y);
	drawList->AddText(ImGui::GetFont(), ImGui::GetFontSize(), textPos, ImGui::GetColorU32(ImGuiCol_Text), mContext.c_str(), nullptr, 0.f, &clipRect);

	ImGui::SameLine();

	// Click
	size = { iconSize.x, 0.f };
	sizeType = EWidgetSize::ABSOLUTE;
	alignment = EWidgetAlignment::RIGHT;

	SetItemLayout();

	ImGui::SetItemAllowOverlap();
	ImGui::ButtonEx((ICON_MDI_ADJUST "" + mWidgetID).c_str(), MathConvert::ToImVec2(size), ImGuiButtonFlags_None);
}
