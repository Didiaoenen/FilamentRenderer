#pragma once

#include "GUI.FRDataWidget.h"

#include <map>

namespace FR::GUI
{
	class FRComboBox
		: public FRDataWidget<int>
	{
	public:
		FRComboBox(int pCurrentChoice = 0);

		template<typename T, typename... TArgs>
		void SetValueChanged(T* tObject, void(T::* tCallback)(TArgs...), auto... tArgs)
		{
			auto argsTuple = std::make_tuple(tArgs...);
			ValueChangedEvent += [tObject, tCallback, argsTuple = std::move(argsTuple)](int p)
				{
					std::apply([tObject, tCallback, p](auto&&... args)
						{
							(tObject->*tCallback)(p, std::forward<decltype(args)>(args)...);
						}, argsTuple);
				};
		}

	protected:
		void _Draw_Impl() override;

	public:
		int currentChoice{ 0 };

		std::map<int, std::string> choices;

		FREvent<int> ItemClickedEvent;
		FREvent<int> ValueChangedEvent;

	};
}

