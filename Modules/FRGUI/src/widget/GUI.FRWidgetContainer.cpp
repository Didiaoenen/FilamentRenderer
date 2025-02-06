#include "GUI.FRWidgetContainer.h"
#include "GUI.FRAWidget.h"

FR::GUI::FRWidgetContainer::~FRWidgetContainer()
{
	RemoveAllWidgets();
}

void FR::GUI::FRWidgetContainer::RemoveWidget(FRAWidget* pWidget)
{
	auto found = std::find_if(mWidgets.begin(), mWidgets.end(), [pWidget](WidgetPair& pair)
		{
			return pair.first == pWidget;
		});

	if (found != mWidgets.end())
	{
		if (found->second == EMemoryMode::INTERNAL_MANAGMENT)
		{
			delete found->first;
			found->first = nullptr;
		}

		mWidgets.erase(found);
	}
}

void FR::GUI::FRWidgetContainer::RemoveAllWidgets()
{
	std::for_each(mWidgets.begin(), mWidgets.end(), [](auto& pair)
		{
			if (pair.second == EMemoryMode::INTERNAL_MANAGMENT)
			{
				delete pair.first;
				pair.first = nullptr;
			}
		});

	mWidgets.clear();
}

void FR::GUI::FRWidgetContainer::ConsiderWidget(FRAWidget* pWidget, bool pManageMemory)
{
	mWidgets.emplace_back(std::make_pair(pWidget, pManageMemory ? EMemoryMode::INTERNAL_MANAGMENT : EMemoryMode::EXTERNAL_MANAGMENT));
	pWidget->SetParent(this);
}

void FR::GUI::FRWidgetContainer::UnconsiderWidget(FRAWidget* pWidget)
{
	auto found = std::find_if(mWidgets.begin(), mWidgets.end(), [pWidget](WidgetPair& pair)
		{
			return pair.first == pWidget;
		});

	if (found != mWidgets.end())
	{
		pWidget->SetParent(nullptr);
		mWidgets.erase(found);
	}
}

void FR::GUI::FRWidgetContainer::ReverseDrawOrder(bool pReversed)
{
	mReversedDrawOrder = pReversed;
}

std::vector<FR::GUI::FRWidgetContainer::WidgetPair>& FR::GUI::FRWidgetContainer::GetWidgets()
{
	return mWidgets;
}

void FR::GUI::FRWidgetContainer::CollectGarbages()
{
	auto found = std::remove_if(mWidgets.begin(), mWidgets.end(), [](WidgetPair& item)
		{
			bool toDestroy = item.first && item.first->IsDestroyed();

			if (toDestroy && item.second == EMemoryMode::INTERNAL_MANAGMENT)
			{
				delete item.first;
				item.first = nullptr;
			}

			return toDestroy;
		});

	mWidgets.erase(found, mWidgets.end());
}

void FR::GUI::FRWidgetContainer::DrawWidgets()
{
	CollectGarbages();

	if (mReversedDrawOrder)
	{
		for (auto it = mWidgets.crbegin(); it != mWidgets.crend(); ++it)
		{
			it->first->Draw();
		}
	}
	else
	{
		for (const auto& widget : mWidgets)
		{
			widget.first->Draw();
		}
	}
}