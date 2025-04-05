#include "GUI.FRMenu.h"

FR::GUI::FRMenuItem::FRMenuItem(const std::string& pName, const std::string& pShortcut, bool pCheckable, bool pChecked)
	: FRDataWidget(mSelected)
	, name(pName)
	, shortcut(pShortcut)
	, checkable(pCheckable)
	, checked(pChecked)
{
}

void FR::GUI::FRMenuItem::_Draw_Impl()
{
	SetItemLayout();

	bool previousValue = checked;

	if (ImGui::MenuItem((name + mWidgetID).c_str(), shortcut.c_str(), checkable ? &checked : nullptr, enabled))
	{
		ClickedEvent.Invoke();
	}

	if (checked != previousValue)
	{
		ValueChangedEvent.Invoke(checked);
		NotifyChange();
	}
}

FR::GUI::FRMenuList::FRMenuList(const std::string& pName, bool pLocked)
	: FRGroup(pName)
	, name(pName)
	, locked(pLocked)
{
}

void FR::GUI::FRMenuList::_Draw_Impl()
{
	SetItemLayout();

	if (ImGui::BeginMenu(name.c_str(), !locked))
	{
		if (!mOpened)
		{
			ClickedEvent.Invoke();
			mOpened = true;
		}

		DrawWidgets();
		ImGui::EndMenu();
	}
	else
	{
		mOpened = false;
	}
}
