#include "GUI.FRAPanel.h"

FR::GUI::FRAPanel::FRAPanel()
{
	mPanelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
}

void FR::GUI::FRAPanel::Draw()
{
	if (enabled)
	{
		_Draw_Impl();
	}
}

const std::string& FR::GUI::FRAPanel::GetPanelID()
{
	return mPanelID;
}
