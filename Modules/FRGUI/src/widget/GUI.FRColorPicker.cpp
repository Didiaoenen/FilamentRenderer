#include "GUI.FRColorPicker.h"

FR::GUI::FRColorPicker::FRColorPicker(bool pEnableAlpha, const Color& pDefaultColor)
	: FRDataWidget<Color>(color)
	, enableAlpha(pEnableAlpha)
	, color(pDefaultColor)
{
}

void FR::GUI::FRColorPicker::_Draw_Impl()
{
	int flags = !enableAlpha ? ImGuiColorEditFlags_NoAlpha : 0;
	bool valueChanged = false;

	if (enableAlpha)
	{
		valueChanged = ImGui::ColorPicker4(mWidgetID.c_str(), &color.r, flags);
	}
	else
	{
		valueChanged = ImGui::ColorPicker3(mWidgetID.c_str(), &color.r, flags);
	}

	if (valueChanged)
	{
		ColorChangedEvent.Invoke(color);
		this->NotifyChange();
	}
}
