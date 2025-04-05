#pragma once

#include "GUI.FRIPlugin.h"

#include <iostream>
#include <functional>

namespace FR::GUI
{
	template<typename T>
	class FRPluginDispatcher
		: public FRIPlugin
	{
	public:
		FRPluginDispatcher() = default;

		virtual void Execute() override
		{
		}

		void RegisterReference(T& pReference)
		{
			mDataPointer = &pReference;
		}

		void RegisterProvider(std::function<void(T)> pProvider)
		{
			mProvider = pProvider;
		}

		void RegisterGatherer(std::function<T(void)> pGatherer)
		{
			mGatherer = pGatherer;
		}

		T Gather()
		{
			return mDataPointer ? *mDataPointer : mGatherer();
		}

		void Provide(T pData)
		{
			if (mValueChanged)
			{
				if (mDataPointer)
				{
					*mDataPointer = pData;
				}
				else
				{
					mProvider(pData);
				}

				mValueChanged = false;
			}
		}

		void NotifyChange()
		{
			mValueChanged = true;
		}

	private:
		T* mDataPointer{ nullptr };

		bool mValueChanged{ false };
		
		std::function<void(T)> mProvider;
		
		std::function<T(void)> mGatherer;

	};
}