#include "GUI.FRInputText.h"

FR::GUI::FRInputText::FRInputText(const std::string& pContent, const std::string& pLabel)
	: FRDataWidget<std::string>(content)
	, content(pContent)
	, label(pLabel)
{
}

void FR::GUI::FRInputText::_Draw_Impl()
{
	SetItemLayout();

	auto cursorPosX = ImGui::GetCursorPosX();

	std::string previousContent = content;

	content.resize(256, '\0');
	uint32_t flags = ImGuiInputTextFlags_EnterReturnsTrue;
	flags = flags | (selectAllOnClick ? ImGuiInputTextFlags_AutoSelectAll : 0);
	bool enterPressed = ImGui::InputText((label + mWidgetID).c_str(), &content[0], 256, flags);
	
	const ImVec2 rectMin = ImGui::GetItemRectMin();
	const ImVec2 rectMax = ImGui::GetItemRectMax();
	DrawItemActivityOutline(MathConvert::ToGlmVec2(rectMin), MathConvert::ToGlmVec2(rectMax));
	
	if (defaultLable && showDefaultLable)
	{
		ImGui::SameLine();
		auto& style = ImGui::GetStyle();
		ImGui::SetCursorPosX(cursorPosX + style.ItemInnerSpacing.x);
		auto defaultText = std::string(ICON_MDI_MAGNIFY " Search...");

		auto fontSize = ImGui::GetFontSize();
		auto spaceSize = static_cast<int>(fontSize) / 2;
		auto textSize = ImGui::CalcTextSize(defaultText.c_str());
		for (size_t i = 0; i < (size.x - textSize.x) / spaceSize + 1; i++)
		{
			defaultText = defaultText + " ";
		}

		ImGui::Text(defaultText.c_str());
	}

	content = content.c_str();
	if (content != previousContent)
	{
		if (content != "")
		{
			if (showDefaultLable)
			{
				defaultLable = false;
			}
		}
		else
		{
			defaultLable = true;
		}

		ContentChangedEvent.Invoke(content);
		NotifyChange();
	}

	if (enterPressed)
	{
		EnterPressedEvent.Invoke(content);
	}
}
