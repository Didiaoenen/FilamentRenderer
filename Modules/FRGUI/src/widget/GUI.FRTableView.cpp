#include "GUI.FRTableView.h"

FR::GUI::FRTableView::FRTableView(const std::string& pName, bool pFixed,
	int pColumnsCount, const glm::vec2& pCellSize, const glm::vec2& pSize, ETableViewLayout pLayout)
	: FRAWidget(pName)
	, name(pName)
	, fixed(pFixed)
	, columnsCount(pColumnsCount)
	, cellSize(pCellSize)
	, layout(pLayout)
{
	size = pSize;
}

void FR::GUI::FRTableView::_Draw_Impl()
{
	auto caculateSize = CaculateSize();

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	flags |= ImGuiTableFlags_ContextMenuInBody;
	if (scrollY)	flags |= ImGuiTableFlags_ScrollY;
	if (resizable)	flags |= ImGuiTableFlags_Resizable;
	if (padOuterX)	flags |= ImGuiTableFlags_PadOuterX;
	if (sizingFixedFit)	flags |= ImGuiTableFlags_SizingFixedFit;

	if (!fixed)
	{
		auto& style = ImGui::GetStyle();
		auto availSize = ImGui::GetContentRegionAvail();
		auto panelWidth = availSize.x - style.ScrollbarSize;
		columnsCount = static_cast<int>(panelWidth / cellSize.x);
	}
	auto count = columnsCount > 0 ? columnsCount : 1;
	if (ImGui::BeginTable(name.c_str(), count, flags, MathConvert::ToImVec2(caculateSize)))
	{
		CollectGarbages();
		
		switch (layout)
		{
		case FR::GUI::ETableViewLayout::Horizontal:
		{
			for (size_t i = 0; i < mWidgets.size(); i++)
			{
				ImGui::TableNextColumn();
				if (auto row = &mWidgets[i])
				{
					row->first->Draw();
				}
			}
		}
			break;
		case FR::GUI::ETableViewLayout::Vertical:
		{
			for (uint8_t i = 0; i < mWidgets.size(); i++)
			{
				ImGui::TableNextRow();
				if (auto row = &mWidgets[i])
				{
					row->first->Draw();
				}
			}
		}
			break;
		default:
			break;
		}

		ImGui::EndTable();
	}
}
