#pragma once

#include "Tools.FREvent.h"

template<class... ArgTypes>
FR::FREvent<ArgTypes...>::ListenerID FR::FREvent<ArgTypes...>::AddListener(Callback pCallback)
{
	ListenerID listenerID = mAvailableListenerID++;
	mCallbacks.emplace(listenerID, pCallback);
	return listenerID;
}

template<class... ArgTypes>
FR::FREvent<ArgTypes...>::ListenerID FR::FREvent<ArgTypes...>::operator+=(Callback pCallback)
{
	return AddListener(pCallback);
}

template<class... ArgTypes>
bool FR::FREvent<ArgTypes...>::RemoveListener(FR::FREvent<ArgTypes...>::ListenerID pListenerID)
{
	return mCallbacks.erase(pListenerID) != 0;
}

template<class... ArgTypes>
bool FR::FREvent<ArgTypes...>::operator-=(FR::FREvent<ArgTypes...>::ListenerID pListenerID)
{
	return RemoveListener(pListenerID);
}

template<class... ArgTypes>
void FR::FREvent<ArgTypes...>::RemoveAllListeners()
{
	mCallbacks.clear();
}

template<class... ArgTypes>
uint64_t FR::FREvent<ArgTypes...>::GetListenerCount()
{
	return mCallbacks.size();
}

template<class... ArgTypes>
void FR::FREvent<ArgTypes...>::Invoke(ArgTypes... pArgs)
{
	for (auto const& [key, value] : mCallbacks)
	{
		value(pArgs...);
	}
}