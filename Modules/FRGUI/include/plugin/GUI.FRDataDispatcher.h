#pragma once

#include <iostream>
#include <functional>
#include "GUI.FRIPlugin.h"

namespace FR::GUI
{
	template<typename T>
	class FRDataDispatcher
		: public FRIPlugin
	{
	public:
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

		virtual void Execute() override {}

	private:
		T* mDataPointer{ nullptr };
		bool mValueChanged{ false };
		std::function<void(T)> mProvider;
		std::function<T(void)> mGatherer;

	};
}