#pragma once

#include "FRRefValue.h"
#include "FRBaseWarp.h"

namespace FR
{
	template<typename T>
	class FRRefWarp
		: public FRBaseWarp
	{
	public:
		FRRefWarp() = default;

		FRRefWarp(T& pValue)
			: mValue(FRRefValue(pValue))
		{
		}

		T& Value()
		{
			return mValue.value();
		}

	protected:
		FRRefValue<T> mValue;

	};
}

