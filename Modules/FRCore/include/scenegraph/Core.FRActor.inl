#pragma once

#include "Core.FRScene.h"
#include "Core.FRComponent.h"
#include "Core.FRCompLight.h"

namespace FR
{
	template<typename T, typename ...Args>
	inline T& FRActor::AddComponent(Args&& ...pArgs)
	{
		static_assert(std::is_base_of<FRComponent, T>::value, "T should derive from AComponent");

		if (auto found = GetComponent<T>(); !found)
		{
			mComponents.insert(mComponents.begin(), std::make_shared<T>(*this, pArgs...));
			T* instance = dynamic_cast<T*>(mComponents.front().get());
			ComponentAddedEvent.Invoke(*instance);
			
			if (auto compLight = dynamic_cast<FRCompLight*>(instance))
			{
				switch (compLight->lightType)
				{
				case ELightType::DIRECTIONAL:
					mScene->AddLight(compLight->GetLight());
					break;
				default:
					break;
				}
			}

			if (IsActive())
			{
				instance->OnAwake();
				instance->OnStart();
				instance->OnEnable();
			}

			return *instance;
		}
		else
		{
			return *found;
		}
	}

	template<typename T>
	inline bool FRActor::RemoveComponent()
	{
		static_assert(std::is_base_of<FRComponent, T>::value, "T should derive from AComponent");

		std::shared_ptr<T> result(nullptr);

		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			result = std::dynamic_pointer_cast<T>(*it);
			if (result)
			{
				ComponentRemovedEvent.Invoke(*result.get());
				mComponents.erase(it);
				return true;
			}
		}

		return false;
	}

	template<typename T>
	inline T* FRActor::GetComponent() const
	{
		static_assert(std::is_base_of<FRComponent, T>::value, "T should derive from AComponent");

		std::shared_ptr<T> result(nullptr);

		for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			result = std::dynamic_pointer_cast<T>(*it);
			if (result)
			{
				return result.get();
			}
		}

		return nullptr;
	}
}