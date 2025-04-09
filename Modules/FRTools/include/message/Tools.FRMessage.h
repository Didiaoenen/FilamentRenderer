#pragma once

#include <map>
#include <array>
#include <memory>
#include <variant>
#include <functional>
#include <unordered_map>

namespace FR
{
	enum class MessageType
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
		static ListenerID AddListener(MessageType pType, T* pObj, void(T::* pCallback)(Args...))
		{
			ListenerID id = ++mAvailableListenerID;
			mMessages[pType].emplace(id, new Wrapper<T, Args...>(pObj, pCallback));
			return mAvailableListenerID;
		}

		static void RemoveListener(MessageType pType, ListenerID pListenerID)
		{
			if (auto found = mMessages[pType].find(pListenerID); found != mMessages[pType].end())
			{
				mMessages[pType].erase(found);
			}
		}

		template<typename... Args>
		static void Invoke(MessageType pType, Args... pArgs)
		{
			if (auto it = mMessages.find(pType); it != mMessages.end())
			{
				for (const auto& [_, value] : it->second)
				{
					auto wrapper = static_cast<WrapperBase<Args...>*>(value);
					wrapper->Invoke(std::forward<decltype(pArgs)>(pArgs)...);
				}
			}
		}

	private:
		inline static ListenerID mAvailableListenerID{ 0 };

		inline static std::map<MessageType, std::unordered_map<ListenerID, void*>> mMessages;

	};
}