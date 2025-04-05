#pragma once

#include "GUI.FRAWidget.h"

namespace FR::GUI
{
	class FRSeparator
		: public FRAWidget
	{
	public:
		FRSeparator() = default;

	protected:
		void _Draw_Impl() override;

	};
}

