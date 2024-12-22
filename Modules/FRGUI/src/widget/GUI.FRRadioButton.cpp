#include "GUI.FRRadioButton.h"

FR::GUI::FRRadioButton::FRRadioButton(bool pSelected, const std::string& pLabel)
	: FRDataWidget<bool>(pSelected)
	, label(pLabel)
{
}

void FR::GUI::FRRadioButton::Select()
{
	mSelected = true;
	ClickedEvent.Invoke(mRadioID);
}

bool FR::GUI::FRRadioButton::IsSelected() const
{
	return mSelected;
}

bool FR::GUI::FRRadioButton::GetRadioID() const
{
	return mRadioID;
}

void FR::GUI::FRRadioButton::_Draw_Impl()
{
	if (ImGui::RadioButton((label + mWidgetID).c_str(), mSelected))
	{
		ClickedEvent.Invoke(mRadioID);
		this->NotifyChange();
	}
}

FR::GUI::FRRadioButtonLinker::FRRadioButtonLinker()
	: FRDataWidget<int>(mSelected)
{
}

void FR::GUI::FRRadioButtonLinker::Link(FRRadioButton& pRadioButton)
{
	pRadioButton.mRadioID = mAvailableRadioID++;
	auto listenerID = pRadioButton.ClickedEvent += std::bind(&FRRadioButtonLinker::OnRadioButtonClicked, this, std::placeholders::_1);

	if (pRadioButton.IsSelected() && mSelected == -1)
	{
		mSelected = pRadioButton.mRadioID;
	}

	mRadioButtons.emplace_back(listenerID, std::ref(pRadioButton));
}

void FR::GUI::FRRadioButtonLinker::Unlink(FRRadioButton& pRadioButton)
{
	auto it = std::find_if(mRadioButtons.begin(), mRadioButtons.end(), 
		[&pRadioButton](std::pair<FREvent<int>::ListenerID, std::reference_wrapper<FRRadioButton>>& pPair)
		{
			return &pPair.second.get() == &pRadioButton;
		});

	if (it != mRadioButtons.end())
	{
		it->second.get().ClickedEvent.RemoveListener(it->first);
		mRadioButtons.erase(it);
	}
}

int FR::GUI::FRRadioButtonLinker::GetSelected() const
{
	return mSelected;
}

void FR::GUI::FRRadioButtonLinker::_Draw_Impl()
{
}

void FR::GUI::FRRadioButtonLinker::OnRadioButtonClicked(int pRadioID)
{
	if (pRadioID != mSelected)
	{
		mSelected = pRadioID;
		ValueChangedEvent.Invoke(mSelected);
		this->NotifyChange();

		for (const auto& [listener, radioButton] : mRadioButtons)
		{
			radioButton.get().mSelected = radioButton.get().mRadioID == mSelected;
		}
	}
}
