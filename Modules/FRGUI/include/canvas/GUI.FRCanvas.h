#pragma once

#include "GUI.FRIDrawable.h"

#include <vector>

namespace FR::GUI
{
	class FRAPanel;

	class FRCanvas
		: public FRIDrawable
	{
	public:
		FRCanvas() = default;

		virtual void Draw() override;

		void AddPanel(FRAPanel* pPanel);

		void RemovePanel(FRAPanel* pPanel);

		void RemoveAllPanels();

	public:
		virtual ~FRCanvas();

	private:
		bool mDockspace{ false };

		std::vector<FRAPanel*> mPanels;

	};
}

