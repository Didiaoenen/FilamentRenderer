#pragma once

#include "GUI.FRLayout.h"
#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRMenuItem
		: public FRDataWidget<bool>
	{
	public:
		FRMenuItem(const std::string& pName, const std::string& pShortcut = "", bool pCheckable = false, bool pChecked = false);

	protected:
		void _Draw_Impl() override;

	public:
		std::string name;
		std::string shortcut;
		bool checked{ false };
		bool checkable{ false };

		FREvent<> ClickedEvent;
		FREvent<bool> ValueChangedEvent;

	private:
		bool mSelected{ false };

	};

	class FRMenuList
		: public FRGroup
	{
	public:
		FRMenuList(const std::string& pName, bool pLocked = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool locked{ false };

		FREvent<> ClickedEvent;

	private:
		bool mOpened{ false };

	};
}


