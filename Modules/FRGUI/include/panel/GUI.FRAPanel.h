#pragma once

#include <string>
#include <glm/glm.hpp>
#include "GUI.FRIDrawable.h"
#include "GUI.FRWidgetContainer.h"

namespace FR::GUI
{
	class FRAPanel
		: public FRIDrawable, public FRWidgetContainer
	{
	public:
		FRAPanel();

		void Draw() override;

		const std::string& GetPanelID() const;

	protected:
		virtual void _Draw_Impl() = 0;

	protected:
		std::string mPanelID;

	public:
		bool enabled = true;

	private:
		static uint64_t __PANEL_ID_INCREMENT;

	};
}

