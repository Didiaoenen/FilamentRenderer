#include "GUI.FRComboBox.h"

FR::GUI::FRComboBox::FRComboBox(int pCurrentChoice)
	: FRDataWidget<int>(currentChoice)
	, currentChoice(pCurrentChoice)
{
}

void FR::GUI::FRComboBox::_Draw_Impl()
{
	SetItemLayout();

	if (choices.find(currentChoice) == choices.end())
	{
		currentChoice = choices.begin()->first;
	}

	if (ImGui::BeginCombo(mWidgetID.c_str(), choices[currentChoice].c_str()))
	{
		for (const auto& [key, value] : choices)
		{
			bool selected = key == currentChoice;

			if (ImGui::Selectable(value.c_str(), selected))
			{
				if (!selected)
				{
					ImGui::SetItemDefaultFocus();
					currentChoice = key;
					ValueChangedEvent.Invoke(currentChoice);
					this->NotifyChange();
				}
				else
				{
					currentChoice = key;
					ItemClickedEvent.Invoke(currentChoice);
				}
			}
		}

		ImGui::EndCombo();
	}
}
