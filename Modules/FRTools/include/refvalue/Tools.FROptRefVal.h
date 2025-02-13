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

		FROptRefVal<T>& operator=(const T& pValue)
		{
			Set(pValue);
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
			return *std::get<T*>(mData);
		}

		const T& Get() const
		{
			if (auto pval = std::get_if<T>(&mData))
			{
				return *pval;
			}
			return *std::get<T*>(mData);
		}

		void Set(const T& pValue)
		{
			if (auto pval = std::get_if<T>(&mData))
			{
				*pval = pValue;
			}
			*std::get<T*>(mData) = pValue;
		}

	private:
		std::variant<T, T*> mData;

	};
}