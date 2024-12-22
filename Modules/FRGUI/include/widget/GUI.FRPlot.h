#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	using fnumber = std::numeric_limits<float>;

	class FRAPlot
		: public FRDataWidget<std::vector<float>>
	{

	public:
		FRAPlot(const std::vector<float>& pData = {}, float pMinScale = fnumber::min(), float pMaxScale = fnumber::max(),
			const glm::vec2& pSize = {}, const std::string& pOverlay = "", const std::string& pLabel = "", int pForceHover = -1);

	protected:
		virtual void _Draw_Impl() override = 0;

	public:
		std::string label;
		std::string overlay;

		int forceHover{ 0 };
		float minScale{ false };
		float maxScale{ false };
		glm::vec2 size{};
		
		std::vector<float> data;

	};

	class FRPlotLines
		: public FRAPlot
	{
	public:
		FRPlotLines(const std::vector<float>& pData = {}, float pMinScale = fnumber::min(), float pMaxScale = fnumber::max(),
			const glm::vec2& pSize = {}, const std::string& pOverlay = "", const std::string& pLabel = "", int pForceHover = -1);

	protected:
		void _Draw_Impl() override;

	};

	class FRPlotHistogram
		: public FRAPlot
	{
	public:
		FRPlotHistogram(const std::vector<float>& pData = {}, float pMinScale = fnumber::min(), float pMaxScale = fnumber::max(),
			const glm::vec2& pSize = {}, const std::string& pOverlay = "", const std::string& pLabel = "", int pForceHover = -1);

	protected:
		void _Draw_Impl() override;

	};
}

