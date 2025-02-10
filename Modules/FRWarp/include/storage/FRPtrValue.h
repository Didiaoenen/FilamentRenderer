#pragma once

namespace FR
{
	template<typename T>
	class FRPtrValue
	{
	public:
		FRPtrValue()
		{
		}

		FRPtrValue(T* pPtr)
			: mStorage(pPtr)
		{
		}

		T* value() const
		{
			return mStorage;
		}

		void reset()
		{
			mStorage = nullptr;
		}

		bool has_value() const
		{
			return mStorage != nullptr;
		}

		T* operator->() const
		{
			return mStorage;
		}

		explicit operator bool() const
		{
			return has_value();
		}

	private:
		T* mStorage{ nullptr };

	};
}

