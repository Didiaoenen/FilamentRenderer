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

		virtual void Draw() override;

		const std::string& GetPanelID() const;

	protected:
		virtual void _Draw_Impl() = 0;

	public:
		bool enabled{ true };

	protected:
		std::string mPanelID;

	private:
		inline static uint64_t __PANEL_ID_INCREMENT{ 0 };

	};
}

