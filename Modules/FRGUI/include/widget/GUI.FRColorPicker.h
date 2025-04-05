#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRColorPicker
		: public FRDataWidget<Color>
	{
	public:
		FRColorPicker(bool pEnableAlpha = false, const Color& pDefaultColor = {});

	protected:
		void _Draw_Impl() override;

	public:
		Color color{};

		bool enableAlpha{ false };

		FREvent<Color&> ColorChangedEvent;

	};
}

