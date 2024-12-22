#pragma once

#include "GUI.FRAWidget.h"
#include "GUI.FRWidgetContainer.h"

namespace FR::GUI
{
	class FRPopup
		: public FRAWidget, public FRWidgetContainer
	{
	public:
		FRPopup(const std::string& pName);

		void OpenPopup();

	protected:
		void _Draw_Impl() override;
	
	public:
		std::string name;

	};
}

