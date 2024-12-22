#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

namespace FR
{
	template<class... ArgTypes>
	class FREvent
	{
	public:
		using ListenerID = uint64_t;

		using Callback = std::function<void(ArgTypes...)>;

		ListenerID AddListener(Callback pCallback);

		ListenerID operator+=(Callback pCallback);

		bool RemoveListener(ListenerID pListenerID);

		bool operator-=(ListenerID pListenerID);

		void RemoveAllListeners();

		uint64_t GetListenerCount();

		void Invoke(ArgTypes... pArgs);

	private:
		ListenerID mAvailableListenerID{ 0 };
		std::unordered_map<ListenerID, Callback> mCallbacks;

	};
}

#include "Tools.FREvent.inl"