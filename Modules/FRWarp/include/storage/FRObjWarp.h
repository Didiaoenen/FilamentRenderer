#pragma once

#include "FRObjValue.h"
#include "FRBaseWarp.h"

namespace FR
{
	template<typename T>
	class FRObjWarp
		: public FRBaseWarp
	{
	public:
		FRObjWarp() = default;

		FRObjWarp(T pValue)
			: mValue(FRObjValue(pValue))
		{
		}

		template<typename ...Args>
		FRObjWarp(Args... pArgs)
			: mValue(pArgs...)
		{
		}

		T& Value()
		{
			return mValue.value();
		}

	protected:
		FRObjValue<T> mValue;

	};
}

