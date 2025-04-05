#pragma once

#include "GUI.FRAWidget.h"

namespace FR::GUI
{
	class FRBullet
		: public FRAWidget
	{
	public:
		FRBullet() = default;

	protected:
		virtual void _Draw_Impl() override;
	
	};
}

