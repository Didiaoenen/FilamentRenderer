#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	template<typename T>
	inline T* FRResourceManager<T>::LoadResource(const std::string& pPath)
	{
		if (auto resource = GetResource(pPath, false); resource)
		{
			return resource;
		}
		else
		{
			if (auto newResource = CreateResource(pPath))
			{
				return RegisterResource(pPath, newResource);
			}
			return nullptr;
		}
	}

	template<typename T>
	inline void FRResourceManager<T>::UnloadResource(const std::string& pPath)
	{
		if (auto resource = GetResource(pPath, false); resource)
		{
			DestroyResource(resource);
			UnregisterResource(pPath);
		}
	}

	template<typename T>
	inline bool FRResourceManager<T>::MoveResource(const std::string& pPath, const std::string& pNewPath)
	{
		if (IsResourceRegistered(pPath) && !IsResourceRegistered(pNewPath))
		{
			T* toMove = mResources.at(pPath);
			UnregisterResource(pPath);
			RegisterResource(pNewPath, toMove);
			return true;
		}

		return false;
	}

	template<typename T>
	inline void FRResourceManager<T>::ReloadResource(const std::string& pPath)
	{
		if (auto resource = GetResource(pPath, false))
		{
			ReloadResource(resource, pPath);
		}
	}

	template<typename T>
	inline bool FRResourceManager<T>::IsResourceRegistered(const std::string& pPath)
	{
		return mResources.find(pPath) != mResources.end();
	}

	template<typename T>
	inline T* FRResourceManager<T>::RegisterResource(const std::string& pPath, T* pInstance)
	{
		if (auto resource = GetResource(pPath, false))
		{
			DestroyResource(resource);
		}

		mResources[pPath] = pInstance;

		return pInstance;
	}

	template<typename T>
	inline void FRResourceManager<T>::UnregisterResource(const std::string& pPath)
	{
		mResources.erase(pPath);
	}

	template<typename T>
	inline T* FRResourceManager<T>::GetResource(const std::string& pPath, bool pTryToLoadIfNotFound)
	{
		if (auto resource = mResources.find(pPath); resource != mResources.end())
		{
			return resource->second;
		}
		else if (pTryToLoadIfNotFound)
		{
			return LoadResource(pPath);
		}

		return nullptr;
	}

	template<typename T>
	inline std::unordered_map<std::string, T*>& FRResourceManager<T>::GetResources()
	{
		return mResources;
	}

	template<typename T>
	inline T* FRResourceManager<T>::operator[](const std::string& pPath)
	{
		return GetResource(pPath);
	}

	template<typename T>
	inline void FRResourceManager<T>::UnloadResources()
	{
		for (auto& [key, value] : mResources)
		{
			DestroyResource(value);
		}

		mResources.clear();
	}

	template<typename T>
	inline FRResourceManager<T>::~FRResourceManager()
	{
		UnloadResources();
	}
}