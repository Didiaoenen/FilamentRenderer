#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRCheckBox
		: public FRDataWidget<bool>
	{
	public:
		FRCheckBox(bool pValue = false, const std::string& pLabel = "");

	protected:
		void SetItemAlign() override;

		void _Draw_Impl() override;

	public:
		std::string label;
		bool value{ false };

		FREvent<bool> ValueChangedEvent;

	};
}

