#include "GUI.FRText.h"
#include <ImguiTextClipped.h>

FR::GUI::FRText::FRText(const std::string& pContent)
	: FRDataWidget(content)
	, content(pContent)
{
}

void FR::GUI::FRText::_Draw_Impl()
{
	SetItemLayout();

	ImGui::Text(content.c_str());
}

FR::GUI::FRTextClickable::FRTextClickable(const std::string& pContent)
	: FRText(pContent)
{
}

void FR::GUI::FRTextClickable::_Draw_Impl()
{
	SetItemLayout();

	bool useless = false;

	if (ImGui::Selectable((content + mWidgetID).c_str(), &useless, ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			DoubleClickedEvent.Invoke();
		}
		else
		{
			ClickedEvent.Invoke();
		}
	}
}

FR::GUI::FRTextColored::FRTextColored(const std::string& pContent, const Color& pColor)
	: FRText(pContent)
	, color(pColor)
{
}

void FR::GUI::FRTextColored::_Draw_Impl()
{
	SetItemLayout();

	ImGui::TextColored(MathConvert::ToImVec4(color), content.c_str());
}

FR::GUI::TextDisabled::TextDisabled(const std::string& pContent)
	: FRText(pContent)
{
}

void FR::GUI::TextDisabled::_Draw_Impl()
{
	ImGui::TextDisabled(content.c_str());
}

FR::GUI::FRTextLabelled::FRTextLabelled(const std::string& pContent, const std::string& pLabel)
	: FRText(pContent)
	, label(pLabel)
{
}

void FR::GUI::FRTextLabelled::_Draw_Impl()
{
	ImGui::LabelText((label + mWidgetID).c_str(), content.c_str());
}

FR::GUI::FRTextSelectable::FRTextSelectable(const std::string& pContent, bool pSelected, bool pDisabled)
	: FRText(pContent)
	, selected(pSelected)
	, disabled(pDisabled)
{
}

void FR::GUI::FRTextSelectable::_Draw_Impl()
{
	if (ImGui::Selectable((content + mWidgetID).c_str(), &selected, disabled ? ImGuiSelectableFlags_Disabled : ImGuiSelectableFlags_None))
	{
		ClickedEvent.Invoke(selected);

		if (selected)
		{
			SelectedEvent.Invoke();
		}
		else
		{
			UnselectedEvent.Invoke();
		}
	}
}

FR::GUI::FRTextWrapped::FRTextWrapped(const std::string& pContent)
	: FRText(pContent)
{
}

void FR::GUI::FRTextWrapped::_Draw_Impl()
{
	ImGui::TextWrapped(content.c_str());
}

FR::GUI::FRTextClipped::FRTextClipped(const std::string& pContent, void* pEnd, const glm::vec2& pMin,
	const glm::vec2& pMax, const glm::vec2* pTextSize, const glm::vec2& pAlign, const glm::vec4* pRect, float pWrapWidth)
	: FRText(pContent)
	, end(pEnd)
	, min(pMin)
	, max(pMax)
	, rect(pRect)
	, align(pAlign)
	, textSize(pTextSize)
	, wrapWidth(pWrapWidth)
{
}

void FR::GUI::FRTextClipped::_Draw_Impl()
{
	ImVec2* imTextSize = nullptr;
	if (textSize)
	{
		auto tempSize = MathConvert::ToImVec2(*textSize);
		imTextSize = &tempSize;
	}
	ImRect* imRect = nullptr;
	if (rect)
	{
		auto tempRect = ImRect(rect->x, rect->y, rect->z, rect->w);
		imRect = &tempRect;
	}
	ImGui::TextClipped(content.c_str(), MathConvert::ToImVec2(min), MathConvert::ToImVec2(max), (char*)end, imTextSize, MathConvert::ToImVec2(align), imRect, wrapWidth);
}
