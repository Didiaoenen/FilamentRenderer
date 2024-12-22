#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace FR
{
	template<typename T>
	class FRResourceManager
	{
	public:
		T* LoadResource(const std::string& pPath);

		void UnloadResource(const std::string& pPath);

		bool MoveResource(const std::string& pPreviousPath, const std::string& pNewPath);

		void ReloadResource(const std::string& pPath);

		bool IsResourceRegistered(const std::string& pPath);

		void UnloadResources();

		T* RegisterResource(const std::string& pPath, T* pInstance);

		void UnregisterResource(const std::string& pPath);

		T* GetResource(const std::string& pPath, bool pTryToLoadIfNotFound = true);

		T* operator[](const std::string& pPath);

		std::unordered_map<std::string, T*>& GetResources();

	protected:
		virtual T* CreateResource(const std::string& pPath) = 0;
		virtual void DestroyResource(T* pResource) = 0;
		virtual void ReloadResource(T* pResource, const std::string& pPath) = 0;

	private:
		inline static std::string __PROJECT_ASSETS_PATH = "";
		inline static std::string __ENGINE_ASSETS_PATH = "";

		std::unordered_map<std::string, T*> mResources;

	};
}

#include "Core.FRResourceManager.inl"
