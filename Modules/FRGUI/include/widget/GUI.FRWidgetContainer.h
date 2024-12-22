#pragma once

#include <vector>
#include <algorithm>
#include "EMemoryMode.h"

namespace FR::GUI
{
	class FRAWidget;

	class FRWidgetContainer
	{
	public:
		FRWidgetContainer() = default;

		void RemoveWidget(FRAWidget* pWidget);
		void RemoveAllWidgets();

		void ConsiderWidget(FRAWidget* pWidget, bool pManageMemory = true);
		void UnconsiderWidget(FRAWidget* pWidget);

		void CollectGarbages();

		virtual void DrawWidgets();

		void ReverseDrawOrder(bool pReversed = true);

		template <typename T, typename ... Args>
		T& CreateWidget(Args&&... pArgs)
		{
			mWidgets.emplace_back(new T(pArgs...), EMemoryMode::INTERNAL_MANAGMENT);
			T& instance = *reinterpret_cast<T*>(mWidgets.back().first);
			instance.SetParent(this);
			return instance;
		}

		std::vector<std::pair<FRAWidget*, EMemoryMode>>& GetWidgets();

	public:
		virtual ~FRWidgetContainer();

	protected:
		bool mReversedDrawOrder{ false };
		std::vector<std::pair<FRAWidget*, EMemoryMode>> mWidgets;

	};
}

