#pragma once

namespace FR
{
	template<typename T>
	class FRObjValue
	{
	public:
		FRObjValue()
		{
		}

		FRObjValue(T pPtr)
			: mStorage(pPtr)
		{
		}

		template<typename ...Args>
		FRObjValue(Args... pArgs)
			: mStorage(pArgs...)
		{
		}

		T& value()
		{
			return mStorage;
		}

		void reset()
		{
			mStorage = {};
		}

		bool has_value() const
		{
			return true;
		}

		explicit operator bool() const
		{
			return has_value();
		}

	private:
		T mStorage{};

	};
}

