#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRRadioButtonLinker;

	class FRRadioButton
		: public FRDataWidget<bool>
	{
		friend FRRadioButtonLinker;

	public:
		FRRadioButton(bool pSelected = false, const std::string& pLabel = "");

		void Select();

		bool IsSelected() const;

		bool GetRadioID() const;

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;

		FREvent<int> ClickedEvent;

	private:
		int mRadioID{ 0 };
		bool mSelected{ false };

	};

	class FRRadioButtonLinker
		: public FRDataWidget<int>
	{
	public:
		FRRadioButtonLinker();

		void Link(FRRadioButton& pRadioButton);

		void Unlink(FRRadioButton& pRadioButton);

		int GetSelected() const;

	protected:
		void _Draw_Impl() override;

	private:
		void OnRadioButtonClicked(int pRadioID);

	public:
		FREvent<int> ValueChangedEvent;

	private:
		int mSelected{ -1 };
		int mAvailableRadioID{ 0 };
		std::vector<std::pair<FREvent<int>::ListenerID, std::reference_wrapper<FRRadioButton>>> mRadioButtons;

	};
}

