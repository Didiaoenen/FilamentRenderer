#include "Editor.FREditorActions.h"

#include "Editor.FRGameView.h"
#include "Editor.FRSceneView.h"
#include "Editor.FRAssetView.h"
#include "Editor.FRInspector.h"
#include "Editor.FRImGuiHelper.h"
#include "Editor.FREditorResources.h"
#include "Editor.FRApplication.h"

#include <Core.FRActor.h>
#include <Core.FRModel.h>
#include <Core.FRScene.h>
#include <Core.FRCompTransform.h>
#include <Core.FRCompModelRenderer.h>
#include <Core.FRCompMaterialRenderer.h>
#include <Core.FRSceneManager.h>

#include <Window.h>
#include <MessageBox.h>
#include <OpenFileDialog.h>
#include <SaveFileDialog.h>

#include <StringExtension.h>
#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

#include <filesystem>
#include <utils/Path.h>

void FR::FREditorActions::ResetLayout()
{
	DelayAction([this]() { FRApplication::GuiHelper()->ResetLayout("Config/layout.ini"); });
}

FR::FREditorActions::EEditorMode FR::FREditorActions::GetCurrentEditorMode()
{
	return mCurrentEditorMode;
}

void FR::FREditorActions::SetCurrentEditorMode(EEditorMode pNewEditorMode)
{
	mCurrentEditorMode = pNewEditorMode;
	EditorModeChangedEvent.Invoke(mCurrentEditorMode);
}

void FR::FREditorActions::Playing()
{
	if (mCurrentEditorMode == EEditorMode::EDIT)
	{
		PlayEvent.Invoke();

		FRApplication::GuiHelper()->GetPanel<FRInspector>()->Refresh();
		FRApplication::GuiHelper()->GetPanel<FRGameView>()->Focus();
		FRSceneManager::Instance()->GetCurrentScene()->Playing();
		SetCurrentEditorMode(EEditorMode::PLAY);
	}
	else
	{
		Stop();
	}
}

void FR::FREditorActions::Pause()
{
	SetCurrentEditorMode(EEditorMode::PAUSE);
}

void FR::FREditorActions::Stop()
{
	if (mCurrentEditorMode != EEditorMode::EDIT)
	{
		//ImGui::GetIO().DisableMouseUpdate = false;
		//FRApplication::GuiHelper()->GetWindow()->SetCursorMode(ECursorMode::NORMAL);
		bool loadedFromDisk = FRSceneManager::Instance()->IsCurrentSceneLoadedFromDisk();
		std::string sceneSourcePath = FRSceneManager::Instance()->GetCurrentSceneSourcePath();

		int64_t focusedActorID = -1;

		if (auto targetActor = FRApplication::GuiHelper()->GetPanel<FRInspector>()->GetTargetActor())
		{
			//focusedActorID = targetActor->GetID();
		}

		//FRSceneManager::Instance()->LoadSceneFromMemory(mSceneBackup);

		if (loadedFromDisk)
		{
			FRSceneManager::Instance()->StoreCurrentSceneSourcePath(sceneSourcePath);
		}

		mSceneBackup.Clear();
		FRApplication::GuiHelper()->GetPanel<FRSceneView>()->Focus();
		
		if (auto actor = FRSceneManager::Instance()->GetCurrentScene()->FindActorByID(focusedActorID))
		{
			FRApplication::GuiHelper()->GetPanel<FRInspector>()->FocusActor(actor);
		}

		SetCurrentEditorMode(EEditorMode::EDIT);
	}
}

void FR::FREditorActions::NextFrame()
{
	if (mCurrentEditorMode == EEditorMode::PLAY || mCurrentEditorMode == EEditorMode::PAUSE)
	{
		SetCurrentEditorMode(EEditorMode::FRAME_BY_FRAME);
	}
}

glm::vec3 FR::FREditorActions::CalculateActorSpawnPoint(float pDistanceToCamera)
{
	auto sceneView = FRApplication::GuiHelper()->GetPanel<FRSceneView>();

	if (auto camera = sceneView->GetCamera())
	{
		return camera->GetPosition() + camera->GetEntity()->GetTransform().GetWorldForward() * pDistanceToCamera;
	}

	return glm::vec3();
}

FR::FRActor* FR::FREditorActions::CreateEmptyActor(bool pFocusOnCreation, FRActor* pParent, const std::string& pName)
{
	const auto currentScene = FRSceneManager::Instance()->GetCurrentScene();
	auto actor = pName.empty() ? currentScene->CreateActor() : currentScene->CreateActor(pName);

	if (pParent)
	{
		actor->SetParent(pParent);
	}

	if (mActorSpawnMode == EActorSpawnMode::FRONT)
	{
		actor->transform->SetLocalPosition(CalculateActorSpawnPoint(10.0f));
	}

	if (pFocusOnCreation)
	{
		SelectActor(actor);
	}

	return actor;
}

FR::FRActor* FR::FREditorActions::CreateActorWithModel(const std::string& pPath, bool pFocusOnCreation, FRActor* pParent, const std::string& pName)
{
	auto actor = CreateEmptyActor(false, pParent, pName);

	auto modelRenderer = actor->AddComponent<FRCompModelRenderer>();

	const auto model = GetService(FRModelManager)[pPath];
	const auto material = GetService(FRMaterialManager)[":Materials/Default.mat"];
	if (model && material)
	{
		auto clone = model->Create();
		modelRenderer->SetModel(clone);
		clone->FillMaterial(material);
	}

	if (pFocusOnCreation)
	{
		SelectActor(actor);
	}

	return actor;
}

bool FR::FREditorActions::DestroyActor(FRActor* pActor)
{
	pActor->MarkAsDestroy();
	return true;
}

void FR::FREditorActions::SelectActor(FRActor* pTarget)
{
	FRApplication::GuiHelper()->GetPanel<FRInspector>()->FocusActor(pTarget);
}

void FR::FREditorActions::UnselectActor()
{
	FRApplication::GuiHelper()->GetPanel<FRInspector>()->UnFocus();
}

bool FR::FREditorActions::IsAnyActorSelected()
{
	return FRApplication::GuiHelper()->GetPanel<FRInspector>()->GetTargetActor();
}

FR::FRActor* FR::FREditorActions::GetSelectedActor()
{
	return FRApplication::GuiHelper()->GetPanel<FRInspector>()->GetTargetActor();
}

void FR::FREditorActions::MoveToTarget(FRActor* pTarget)
{
	return FRApplication::GuiHelper()->GetPanel<FRSceneView>()->GetCameraController().MoveToTarget(pTarget);
}

std::string FR::FREditorActions::GetResourcePath(const std::string& pPath, bool pIsFromEngine)
{
	std::string result = pPath;
	auto engineAssetsPath = FRPathUtils::GetEngineAssetsPath();
	auto projectAssetsPath = FRPathUtils::GetProjectAssetsPath();
	if (StringExtension::Replace(result, pIsFromEngine ? engineAssetsPath : projectAssetsPath, ""))
	{
		if (!result.empty())
		{
			result = std::string(result.data() + 1, result.data() + result.size());
		}

		if (pIsFromEngine)
		{
			result = ':' + result;
		}
	}

	return result;
}

void FR::FREditorActions::LoadEmptyScene()
{
	if (mCurrentEditorMode != EEditorMode::EDIT)
	{
		Stop();
	}

	FRSceneManager::Instance()->LoadEmptyLightedScene();
}

void FR::FREditorActions::LoadSceneFromDisk(const std::string& pPath, bool pAbsolute)
{
	if (mCurrentEditorMode != EEditorMode::EDIT)
	{
		Stop();
	}

	FRSceneManager::Instance()->LoadScene(pPath, pAbsolute);
	FRApplication::GuiHelper()->GetPanel<FRSceneView>()->Focus();
}

void FR::FREditorActions::DelayAction(std::function<void()> pAction, uint32_t pFrames)
{
	mDelayedActions.emplace_back(pFrames + 1, pAction);
}

void FR::FREditorActions::ExecuteDelayedActions()
{
	std::for_each(mDelayedActions.begin(), mDelayedActions.end(), [](std::pair<uint32_t, std::function<void()>>& pElement)
		{
			--pElement.first;

			if (pElement.first == 0)
			{
				pElement.second();
			}
		});

	mDelayedActions.erase(std::remove_if(mDelayedActions.begin(), mDelayedActions.end(), [](std::pair<uint32_t, std::function<void()>>& pElement)
		{
			return pElement.first == 0;
		}), mDelayedActions.end());
}
