#include "GUI.FRColorEdit.h"

FR::GUI::FRColorEdit::FRColorEdit(bool pEnableAlpha, const Color& pDefaultColor)
	: FRDataWidget<Color>(color)
	, enableAlpha(pEnableAlpha)
	, color(pDefaultColor)
{
}

void FR::GUI::FRColorEdit::_Draw_Impl()
{
	SetItemLayout();

	int flags = !enableAlpha ? ImGuiColorEditFlags_NoAlpha : 0;
	bool valueChanged = false;

	if (enableAlpha)
	{
		valueChanged = ImGui::ColorEdit4(mWidgetID.c_str(), &color.r, flags);
	}
	else
	{
		valueChanged = ImGui::ColorEdit3(mWidgetID.c_str(), &color.r, flags);
	}

	if (valueChanged)
	{
		ColorChangedEvent.Invoke(color);
		NotifyChange();
	}
}
