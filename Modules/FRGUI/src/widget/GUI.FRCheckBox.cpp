#include "GUI.FRCheckBox.h"

FR::GUI::FRCheckBox::FRCheckBox(bool pValue, const std::string& pLabel)
	: FRDataWidget<bool>(value)
	, value(pValue)
	, label(pLabel)
{
}

void FR::GUI::FRCheckBox::SetItemAlign()
{
	switch (alignment)
	{
	case EWidgetAlignment::LEFT:
	{
		if (position != glm::vec2{ 0.f, 0.f })
		{
			ImGui::SetCursorPosX(position.x);
		}
	}
		break;
	case EWidgetAlignment::CENTER:
		break;
	case EWidgetAlignment::RIGHT:
	{
		auto contentSize = ImGui::GetWindowContentRegionMax();
		ImGui::SetCursorPosX(contentSize.x - position.x - 22.0f);
	}
		break;
	default:
		break;
	}
}

void FR::GUI::FRCheckBox::_Draw_Impl()
{
	SetItemLayout();

	bool previousValue = value;

	ImGui::Checkbox((label + mWidgetID).c_str(), &value);

	if (value != previousValue)
	{
		ValueChangedEvent.Invoke(value);
		NotifyChange();
	}
}
