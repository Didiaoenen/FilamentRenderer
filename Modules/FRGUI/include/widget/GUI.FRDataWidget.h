#pragma once

#include "GUI.FRAWidget.h"
#include "GUI.FRPluginDispatcher.h"

namespace FR::GUI
{
	template <typename T>
	class FRDataWidget
		: public FRAWidget
	{
	public:
		FRDataWidget(T& pDataHolder) 
			: mData(pDataHolder)
		{
		};

		virtual void Draw() override;

		void NotifyChange();

	protected:
		T& mData;

	};

	template<typename T>
	inline void FRDataWidget<T>::Draw()
	{
		if (enabled)
		{
			if (auto plugin = GetPlugin<FRPluginDispatcher<T>>())
			{
				mData = plugin->Gather();
			}

			FRAWidget::Draw();

			if (auto plugin = GetPlugin<FRPluginDispatcher<T>>())
			{
				plugin->Provide(mData);
			}
		}
	}

	template<typename T>
	inline void FRDataWidget<T>::NotifyChange()
	{
		if (auto plugin = GetPlugin<FRPluginDispatcher<T>>())
		{
			plugin->NotifyChange();
		}
	}
}