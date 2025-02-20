#pragma once

#include <string>
#include <tinyxml2.h>
#include <Tools.FREvent.h>

namespace FR
{
	class FRScene;

	class FRSceneManager
	{
	public:
		FRSceneManager();

		void Update();

		void LoadEmptyScene();

		void LoadAndPlayDelayed(const std::string& pPath, bool pAbsolute = false);

		FRScene* LoadEmptyLightedScene();

		bool LoadScene(const std::string& pPath, bool pAbsolute = false);

		bool LoadSceneFromMemory(tinyxml2::XMLDocument& pDoc);

		void UnloadCurrentScene();

		FRScene* GetCurrentScene() const;

		std::string GetCurrentSceneSourcePath() const;

		bool IsCurrentSceneLoadedFromDisk() const;

		void StoreCurrentSceneSourcePath(const std::string& pPath);

		void ForgetCurrentSceneSourcePath();

		static FRSceneManager* Instance();

	public:
		virtual ~FRSceneManager();

	public:
		FREvent<> SceneLoadEvent;
		FREvent<> SceneUnloadEvent;
		FREvent<const std::string&> CurrentSceneSourcePathChangedEvent;

	private:
		inline static FRSceneManager* sInstance{ nullptr };
		FRScene* mCurrentScene{ nullptr };

		std::string mSceneRootFolder;
		std::string mCurrentSceneSourcePath;

		bool mCurrentSceneLoadedFromPath{ false };

		std::function<void()> mDelayedLoadCall;
	};
}
