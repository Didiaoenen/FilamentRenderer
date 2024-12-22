#pragma once

#include <vector>
#include "GUI.FRIPlugin.h"

namespace FR::GUI
{
	class FRPluginable
	{
	public:
		template<typename T>
		T* GetPlugin()
		{
			static_assert(std::is_base_of<FRIPlugin, T>::value, "T should derive from IPlugin");

			for (auto it = mPlugins.begin(); it != mPlugins.end(); ++it)
			{
				if (T* result = dynamic_cast<T*>(*it); result)
				{
					return result;
				}
			}

			return nullptr;
		}

		template<typename T, typename... Args>
		T& AddPlugin(Args&& ... pArgs)
		{
			static_assert(std::is_base_of<FRIPlugin, T>::value, "T should derive from IPlugin");

			T* newPlugin = new T(std::forward<Args>(pArgs)...);
			mPlugins.push_back(newPlugin);
			return *newPlugin;
		}

		void ExecutePlugins()
		{
			for (auto& plugin : mPlugins)
			{
				plugin->Execute();
			}
		}

		void RemoveAllPlugins()
		{
			for (auto& plugin : mPlugins)
			{
				delete plugin;
			}
			mPlugins.clear();
		}

	public:
		~FRPluginable()
		{
			RemoveAllPlugins();
		}

	private:
		std::vector<FRIPlugin*> mPlugins;

	};
}