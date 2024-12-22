#pragma once

#include <optional>

namespace FR
{
	template <typename T>
	class FROptRef
	{
	public:
		FROptRef() = default;

		FROptRef(std::nullopt_t) : mStorage() {}

		FROptRef(T* pPtr) : mStorage(std::ref(*pPtr)) {}

		FROptRef(T& pValue) : mStorage(std::ref(pValue)) {}

		FROptRef(const FROptRef& pOther) : mStorage(pOther.mStorage) {}

		FROptRef& operator=(T* pPtr)
		{
			mStorage = pPtr ? std::optional(std::ref(*pPtr)) : std::nullopt;
			return *this;
		}

		FROptRef& operator=(const FROptRef& pOther)
		{
			mStorage = pOther.mStorage;
			return *this;
		}

		T& value() const
		{
			return mStorage.value().get();
		}

		T& value_or(const T& pOther) const
		{
			return has_value() ? value() : pOther;
		}

		bool has_value() const
		{
			return mStorage.has_value();
		}

		void reset()
		{
			mStorage = std::nullopt;
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