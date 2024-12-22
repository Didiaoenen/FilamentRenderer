#include "GUI.FRPlot.h"

FR::GUI::FRAPlot::FRAPlot(const std::vector<float>& pData, float pMinScale, float pMaxScale, const glm::vec2& pSize, const std::string& pOverlay, const std::string& pLabel, int pForceHover)
	: FRDataWidget(data)
	, data(pData)
	, minScale(pMinScale)
	, maxScale(pMaxScale)
	, size(pSize)
	, overlay(pOverlay)
	, label(pLabel)
	, forceHover(pForceHover)
{
}

FR::GUI::FRPlotLines::FRPlotLines(const std::vector<float>& pData, float pMinScale, float pMaxScale, const glm::vec2& pSize, const std::string& pOverlay, const std::string& pLabel, int pForceHover)
	: FRAPlot(pData, pMinScale, pMaxScale, pSize, pOverlay, pLabel, pForceHover)
{
}

void FR::GUI::FRPlotLines::_Draw_Impl()
{
	ImGui::PlotLines((label + mWidgetID).c_str(), data.data(), static_cast<int>(data.size()), 0, overlay.c_str(), minScale, maxScale, MathConvert::ToImVec2(size), sizeof(float));
}

FR::GUI::FRPlotHistogram::FRPlotHistogram(const std::vector<float>& pData, float pMinScale, float pMaxScale, const glm::vec2& pSize, const std::string& pOverlay, const std::string& pLabel, int pForceHover)
	: FRAPlot(pData, pMinScale, pMaxScale, pSize, pOverlay, pLabel, pForceHover)
{
}

void FR::GUI::FRPlotHistogram::_Draw_Impl()
{
	ImGui::PlotHistogram((label + mWidgetID).c_str(), data.data(), static_cast<int>(data.size()), 0, overlay.c_str(), minScale, maxScale, MathConvert::ToImVec2(size), sizeof(float));
}
