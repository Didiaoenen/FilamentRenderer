#include "GUI.FRAPanel.h"

namespace FR::GUI
{
	uint64_t FRAPanel::__PANEL_ID_INCREMENT = 0;
}

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

const std::string& FR::GUI::FRAPanel::GetPanelID() const
{
	return mPanelID;
}
