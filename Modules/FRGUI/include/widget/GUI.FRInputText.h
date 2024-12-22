#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRInputText
		: public FRDataWidget<std::string>
	{
	public:
		FRInputText(const std::string& pContent = "", const std::string& pLabel = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;
		std::string content;
		bool defaultLable{ true };
		bool showDefaultLable{ true };
		bool selectAllOnClick{ false };

		FREvent<std::string> EnterPressedEvent;
		FREvent<std::string> ContentChangedEvent;

	};
}

