#pragma once

#include "GUI.FRAWidget.h"
#include "GUI.FRWidgetContainer.h"

namespace FR::GUI
{
	enum class ETableViewLayout
	{
		Horizontal,
		Vertical,
	};

	class FRTableView
		: public FRAWidget, public FRWidgetContainer
	{
	public:
		FRTableView(const std::string& pName, bool pFixed, int pColumnsCount,
			const glm::vec2& pCellSize, const glm::vec2& pSize = {}, ETableViewLayout pLayout = ETableViewLayout::Horizontal);

	protected:
		void _Draw_Impl() override;

	public:
		std::string name;

		glm::vec2 cellSize{};

		int columnsCount{ 1 };

		bool fixed{ true };

		bool scrollY{ false };

		bool resizable{ false };

		bool padOuterX{ false };

		bool sizingFixedFit{ false };

		ETableViewLayout layout{ ETableViewLayout::Horizontal };

	};
}