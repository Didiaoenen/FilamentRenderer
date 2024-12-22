#pragma once

#include "GUI.FRAPanelTrans.h"

namespace FR::GUI
{
	class FRPanelUndecorated
		: public FRAPanelTrans
	{
	public:
		void _Draw_Impl() override;

	private:
		int CollectFlags();

	};
}

