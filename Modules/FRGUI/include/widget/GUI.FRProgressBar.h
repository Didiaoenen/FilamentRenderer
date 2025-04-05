#pragma once

#include "GUI.FRAWidget.h"

namespace FR::GUI
{
	class FRProgressBar
		: public FRAWidget
	{
	public:
		FRProgressBar(float pFraction = 0.f, const glm::vec2& pSize = {}, const std::string& pOverlay = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string overlay;

		float fraction{ false };

	};
}

