#pragma once

#include <optional>

namespace FR
{
	template<typename T>
	class FRRefValue
	{
	public:
		FRRefValue()
		{
		}

		FRRefValue(T& pValue)
			: mStorage(std::ref(pValue))
		{
		}

		T& value() const
		{
			return mStorage.value().get();
		}

		void reset()
		{
			mStorage = std::nullopt;
		}

		bool has_value() const
		{
			return mStorage.has_value();
		}

		T* operator->() const
		{
			return &mStorage.value().get();
		}

		explicit operator bool() const
		{
			return has_value();
		}

	private:
		std::optional<std::reference_wrapper<T>> mStorage;
	};
}