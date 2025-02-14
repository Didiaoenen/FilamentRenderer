#pragma once

#include <string>
#include <optional>
#include <functional>
#include <tinyxml2.h>
#include <glm/glm.hpp>
#include <Tools.FREvent.h>

namespace FR
{
	class FRActor;

	class FREditorActions
	{
	public:

		enum class EActorSpawnMode : uint8_t
		{
			ORIGIN,
			FRONT,
		};

		enum class EEditorMode : uint8_t
		{
			EDIT,
			PLAY,
			PAUSE,
			FRAME_BY_FRAME,
		};

#pragma region SETTINGS
		void ResetLayout();
#pragma endregion

#pragma region GAME
		void Playing();

		void Pause();

		void Stop();

		void NextFrame();

		EEditorMode GetCurrentEditorMode();

		void SetCurrentEditorMode(EEditorMode pNewEditorMode);
#pragma endregion

#pragma region ACTOR_CREATION_DESTRUCTION
		glm::vec3 CalculateActorSpawnPoint(float pDistanceToCamera);

		FRActor* CreateEmptyActor(bool pFocusOnCreation = true, FRActor* pParent = nullptr, const std::string& pName = "");

		FRActor* CreateActorWithModel(const std::string& pPath, bool pFocusOnCreation = true, FRActor* pParent = nullptr, const std::string& pName = "");
		
		bool DestroyActor(FRActor* pActor);
#pragma endregion

#pragma region ACTOR_MANIPULATION
		void SelectActor(FRActor* pTarget);

		void UnselectActor();

		bool IsAnyActorSelected();

		FRActor* GetSelectedActor();

		void MoveToTarget(FRActor* pTarget);
#pragma endregion

#pragma region RESOURCE_MANAGEMENT
		std::string GetResourcePath(const std::string& pPath, bool pIsFromEngine = false);
#pragma endregion

#pragma region SCENE
		void LoadEmptyScene();

		void LoadSceneFromDisk(const std::string& pPath, bool pAbsolute = false);
#pragma endregion

#pragma region ACTION_SYSTEM
		void DelayAction(std::function<void()> pAction, uint32_t pFrames = 1);

		void ExecuteDelayedActions();
#pragma endregion

	public:
		FREvent<> PlayEvent;
		FREvent<FRActor*> ActorSelectedEvent;
		FREvent<FRActor*> ActorUnselectedEvent;
		FREvent<EEditorMode> EditorModeChangedEvent;

	private:
		EEditorMode mCurrentEditorMode{ EEditorMode::EDIT };
		EActorSpawnMode mActorSpawnMode{ EActorSpawnMode::ORIGIN };

		std::vector<std::pair<uint32_t, std::function<void()>>> mDelayedActions;

		tinyxml2::XMLDocument mSceneBackup;

	};
}
