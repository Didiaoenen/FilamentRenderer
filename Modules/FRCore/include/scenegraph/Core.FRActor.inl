#pragma once

#include "Core.FRScene.h"
#include "Core.FRComponent.h"
#include "Core.FRCompLight.h"

namespace FR
{
	template<typename T, typename ...Args>
	inline T* FRActor::AddComponent(Args&& ...pArgs)
	{
		static_assert(std::is_base_of<FRComponent, T>::value, "T should derive from AComponent");

		if (auto found = GetComponent<T>(); !found)
		{
			mComponents.emplace_back(new T(*this, std::forward<Args>(pArgs)...));
			T* component = dynamic_cast<T*>(mComponents.back());
			ComponentAddedEvent.Invoke(component);
			
			if (IsActive())
			{
				component->OnAwake();
				//component->OnStart();
				//component->OnEnable();
			}

			return component;
		}
		else
		{
			return found;
		}
	}

	template<typename T>
	inline bool FRActor::RemoveComponent()
	{
		static_assert(std::is_base_of<FRComponent, T>::value, "T should derive from AComponent");

		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if (auto result = dynamic_cast<T*>(*it))
			{
				ComponentRemovedEvent.Invoke(result);
				mComponents.erase(it);
				return true;
			}
		}

		return false;
	}

	template<typename T>
	inline T* FRActor::GetComponent()
	{
		static_assert(std::is_base_of<FRComponent, T>::value, "T should derive from AComponent");

		for (auto it = mComponents.begin(); it != mComponents.end(); it++)
		{
			if (auto result = dynamic_cast<T*>(*it))
			{
				return result;
			}
		}

		return nullptr;
	}
}