#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRColorEdit
		: public FRDataWidget<Color>
	{
	public:
		FRColorEdit(bool pEnableAlpha = false, const Color& pDefaultColor = {});

	protected:
		void _Draw_Impl() override;

	public:
		Color color{};

		bool enableAlpha{ false };

		FREvent<Color&> ColorChangedEvent;

	};
}

