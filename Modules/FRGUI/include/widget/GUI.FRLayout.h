#pragma once

#include "GUI.FRAWidget.h"
#include "GUI.FRDataWidget.h"
#include "GUI.FRWidgetContainer.h"

#include <array>

namespace FR::GUI
{
	template <size_t _Size>
	class FRColumns
		: public FRAWidget, public FRWidgetContainer
	{
	public:
		FRColumns()
		{
			widths.fill(-1.f);
		}

	protected:
		virtual void _Draw_Impl() override
		{
			ImGui::Columns(static_cast<int>(_Size), ("##" + mWidgetID).c_str(), false);

			int counter = 0;

			CollectGarbages();

			for (auto it = mWidgets.begin(); it != mWidgets.end();)
			{
				it->first->Draw();

				++it;

				if (it != mWidgets.end())
				{
					if (widths[counter] != -1.f)
					{
						ImGui::SetColumnWidth(counter, widths[counter]);
					}

					ImGui::NextColumn();
				}

				++counter;

				if (counter == _Size)
				{
					counter = 0;
				}
			}

			ImGui::Columns(1);
		}

	public:
		std::array<float, _Size> widths;

	};

	class FRDummy
		: public FRAWidget
	{
	public:
		FRDummy(const glm::vec2& pSize = {});

	protected:
		void _Draw_Impl() override;

	};

	class FRGroup
		: public FRAWidget, public FRWidgetContainer
	{
	public:
		FRGroup(const std::string& pName = "");
	
	protected:
		virtual void _Draw_Impl() override;

	};

	class FRGroupCollapsable
		: public FRGroup
	{
	public:
		FRGroupCollapsable(const std::string& pName = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;

		bool opened{ true };

		bool closable{ false };
		
		FREvent<> OpenEvent;
		FREvent<> CloseEvent;
	
	};

	class FRNewLine
		: public FRAWidget
	{
	public:
		FRNewLine() = default;

	protected:
		void _Draw_Impl() override;

	};

	class FRSpacing
		: public FRAWidget
	{
	public:
		FRSpacing(uint16_t pSpaces = 1);

	protected:
		void _Draw_Impl() override;

	public:
		uint16_t spaces{ 1 };
	};

	class FRTreeNode
		: public FRDataWidget<std::string>, public FRWidgetContainer
	{
	public:
		FRTreeNode(
			const std::string& pName = "", const std::string& pOpenIcon = "",
			const std::string& pCloseIcon = "", bool pArrowClickToOpen = false);

		void Open();

		void Close();

		bool IsOpened();

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;

		bool leaf{ false };

		bool framed{ false };

		bool selected{ false };

		FREvent<> ClosedEvent;
		FREvent<> OpenedEvent;

		FREvent<> ClickedEvent;
		FREvent<> DoubleClickedEvent;

	private:
		bool mOpened{ false };
		
		bool mShouldOpen{ false };
	
		bool mShouldClose{ false };
		
		bool mArrowClickToOpen{ false };

		std::string mOpenIcon;
		std::string mCloseIcon;

	};
}

