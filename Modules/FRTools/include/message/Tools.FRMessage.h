#pragma once

#include <map>
#include <array>
#include <memory>
#include <variant>
#include <functional>
#include <unordered_map>

namespace FR
{
	enum class EventType
	{
		SDL,
		LOG,
		MAX,
	};
	
	class FRMessage
	{
	public:
		using ListenerID = uint64_t;

		template<typename... Args>
		class WrapperBase
		{
		public:
			virtual void Invoke(Args... pArgs) = 0;
		};

		template<typename T, typename... Args>
		class Wrapper : public WrapperBase<Args...>
		{
		public:
			Wrapper(T* pObj, void(T::* pCallback)(Args...)) :
				obj(pObj), callback(pCallback)
			{
			}

			void Invoke(Args... pArgs) override
			{
				(obj->*callback)(pArgs...);
			}

		private:
			T* obj;
			void (T::* callback)(Args...);
		};

		template<typename T, typename... Args>
		static ListenerID AddListener(EventType pType, T* pObj, void(T::* pCallback)(Args...))
		{
			ListenerID id = ++mAvailableListenerID;
			mEvents[pType].emplace(id, new Wrapper<T, Args...>(pObj, pCallback));
			return mAvailableListenerID;
		}

		static void RemoveListener(EventType pType, ListenerID pListenerID)
		{
			if (auto found = mEvents[pType].find(pListenerID); found != mEvents[pType].end())
			{
				mEvents[pType].erase(found);
			}
		}

		template<typename... Args>
		static void Invoke(EventType pType, Args... pArgs)
		{
			if (auto it = mEvents.find(pType); it != mEvents.end())
			{
				for (auto& [key, value] : it->second)
				{
					auto wrapper = static_cast<WrapperBase<Args...>*>(value);
					wrapper->Invoke(pArgs...);
				}
			}
		}

	private:
		inline static ListenerID mAvailableListenerID{ 0 };
		inline static std::map<EventType, std::unordered_map<ListenerID, void*>> mEvents;
	};
}