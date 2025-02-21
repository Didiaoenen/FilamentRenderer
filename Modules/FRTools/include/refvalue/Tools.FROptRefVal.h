#pragma once

#include <variant>
#include <optional>
#include <stdexcept>

#include "Tools.FROptRef.h"

namespace FR
{
	template <typename T>
	class FROptRefVal
	{
	public:
		FROptRefVal(FROptRef<T> pRef = std::nullopt)
		{
			if (pRef)
			{
				mData = &pRef.value();
			}
			else
			{
				mData = T();
			}
		}

		FROptRefVal<T>& operator=(T& pValue)
		{
			mData = &pValue;
			return *this;
		}

		T const* operator->() const
		{
			return &Get();
		}

		T* operator->()
		{
			return &GetRef();
		}

		operator T& ()
		{
			return GetRef();
		}

		T& GetRef()
		{
			if (auto pval = std::get_if<T>(&mData))
			{
				return *pval;
			}
			else
			{
				return *std::get<T*>(mData);
			}
		}

		const T& Get() const
		{
			if (auto pval = std::get_if<T>(&mData))
			{
				return *pval;
			}
			else
			{
				return *std::get<T*>(mData);
			}
		}

		void Set(const T& pValue)
		{
			if (auto pval = std::get_if<T>(&mData))
			{
				*pval = pValue;
			}
			else
			{
				*std::get<T*>(mData) = pValue;
			}
		}

	private:
		std::variant<T, T*> mData;

	};
}