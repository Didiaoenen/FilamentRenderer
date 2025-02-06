#pragma once

#include <vector>
#include <algorithm>
#include "EMemoryMode.h"

namespace FR::GUI
{
	class FRAWidget;

	class FRWidgetContainer
	{
		using WidgetPair = std::pair<FRAWidget*, EMemoryMode>;

	public:
		FRWidgetContainer() = default;

		void RemoveWidget(FRAWidget* pWidget);

		void RemoveAllWidgets();

		void ConsiderWidget(FRAWidget* pWidget, bool pManageMemory = true);

		void UnconsiderWidget(FRAWidget* pWidget);

		void ReverseDrawOrder(bool pReversed = true);

		std::vector<WidgetPair>& GetWidgets();

		void CollectGarbages();

		virtual void DrawWidgets();

		template <typename T, typename ... Args>
		T& CreateWidget(Args&&... pArgs)
		{
			mWidgets.emplace_back(new T(pArgs...), EMemoryMode::INTERNAL_MANAGMENT);
			T& instance = *reinterpret_cast<T*>(mWidgets.back().first);
			instance.SetParent(this);
			return instance;
		}

	public:
		virtual ~FRWidgetContainer();

	protected:
		bool mReversedDrawOrder{ false };
		std::vector<WidgetPair> mWidgets;

	};
}

