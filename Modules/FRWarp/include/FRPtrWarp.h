#pragma once

#include "FRPtrValue.h"
#include "FRBaseWarp.h"

namespace FR
{
	template<typename T>
	class FRPtrWarp
		: public FRBaseWarp
	{
	public:
		FRPtrWarp() = default;

		FRPtrWarp(T* pValue)
			: mValue(FRPtrValue(pValue))
		{
		}

		T* Value()
		{
			return mValue.value();
		}

		void Reset()
		{
			mValue.reset();
		}

		T* operator->()
		{
			return Value();
		}

	protected:
		FRPtrValue<T> mValue;

	};
}

