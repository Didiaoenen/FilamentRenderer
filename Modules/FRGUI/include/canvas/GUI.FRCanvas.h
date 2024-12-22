#pragma once

#include <vector>
#include "GUI.FRIDrawable.h"

namespace FR::GUI
{
	class FRAPanel;

	class FRCanvas
		: public FRIDrawable
	{
	public:
		FRCanvas() = default;

		void AddPanel(FRAPanel* pPanel);

		void RemovePanel(FRAPanel* pPanel);

		void RemoveAllPanels();

		virtual void Draw() override;

	private:
		bool mDockspace{ false };
		std::vector<FRAPanel*> mPanels;

	};
}

