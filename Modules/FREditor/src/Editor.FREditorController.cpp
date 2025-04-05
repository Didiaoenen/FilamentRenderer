#include "Editor.FREditorController.h"

#include "Editor.FRApplication.h"
#include "Editor.FRImGuiHelper.h"
#include "Editor.FREditorActions.h"
#include "Editor.FREditorResources.h"

#include "Editor.FRToolBar.h"
#include "Editor.FRConsole.h"
#include "Editor.FRGameView.h"
#include "Editor.FRHierarchy.h"
#include "Editor.FRInspector.h"
#include "Editor.FRSceneView.h"
#include "Editor.FRAssetView.h"
#include "Editor.FRAssetBrowser.h"
#include "Editor.FRMaterialEditor.h"

#include <Core.FRMesh.h>
#include <Core.FRModel.h>
#include <Core.FRShader.h>
#include <Core.FRMaterial.h>
#include <Core.FRRenderable.h>
#include <Core.FREnvironment.h>
#include <Core.FRSceneManager.h>
#include <Core.FRSceneRenderer.h>

#include <MathConvert.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

namespace
{
	FR::FRGameView* gameView = nullptr;
	FR::FRSceneView* sceneView = nullptr;
	FR::FRAssetView* assetView = nullptr;

	FR::FRRenderable* planeRenderable = nullptr;
}

FR::FREditorController::FREditorController()
{
	SetupUI();

	auto scene = FRSceneManager::Instance()->LoadEmptyLightedScene();

	auto planeModel = FRApplication::EditorResources()->GetModel("Plane");
	auto gridShader = FRApplication::EditorResources()->GetShader("Grid");
	auto iblTexture = FRApplication::EditorResources()->GetTexture("IBL");
	auto skyboxTexture = FRApplication::EditorResources()->GetTexture("Skybox");

	planeRenderable = new FRRenderable(new FREntity(FRFilamentHelper::CreateEntity()));

	for (auto& mesh : planeModel->GetMeshes())
	{
		planeRenderable->BuildMesh(mesh);
	}

	auto t = glm::mat4(1.0f);
	auto transform = glm::translate(t, glm::vec3(0.0f, -10.0f, 0.0f)) * glm::scale(t, glm::vec3(10000.0f, 1.0f, 10000.0f));
	planeRenderable->SetTransform(0, transform);

	auto material = new FRMaterial(gridShader);
	material->SetParameter("baseColor", MathConvert::ToFVec3({ 0.176f, 0.176f, 0.176f }));
	material->SetTransparencyMode(FRMaterialInstanceWarp::ETransparencyMode::DEFAULT);
	material->SetCullingMode(FRMaterialInstanceWarp::ECullingMode::NONE);

	planeRenderable->SetMaterialAtIndex(0, material);

	scene->AddGizmo(planeRenderable);

	auto environment = new FREnvironment(skyboxTexture, iblTexture);

	scene->SetEnvironment(environment);
}

void FR::FREditorController::SetupUI()
{
	FRServiceLocator::Provide<FREditorActions>(editorActions);

	FRPanelWindowSettings settings{ .dockable = true, .closable = true, .collapsable = true };

	FRApplication::GuiHelper()->AddPanel<FRToolBar>("MenuBar");
	FRApplication::GuiHelper()->AddPanel<FRConsole>("Console", true, settings);
	FRApplication::GuiHelper()->AddPanel<FRGameView>("GameView", true, settings);
	FRApplication::GuiHelper()->AddPanel<FRHierarchy>("Hierarchy", true, settings);
	FRApplication::GuiHelper()->AddPanel<FRInspector>("Inspector", true, settings);
	FRApplication::GuiHelper()->AddPanel<FRSceneView>("SceneView", true, settings);
	FRApplication::GuiHelper()->AddPanel<FRAssetView>("AssetView", false, settings);
	FRApplication::GuiHelper()->AddPanel<FRAssetBrowser>("AssetBrowser", true, settings);
	FRApplication::GuiHelper()->AddPanel<FRMaterialEditor>("MaterialEditor", false, settings);

	gameView = FRApplication::GuiHelper()->GetPanel<FRGameView>();
	sceneView = FRApplication::GuiHelper()->GetPanel<FRSceneView>();
	assetView = FRApplication::GuiHelper()->GetPanel<FRAssetView>();

	sceneView->Focus();
}

void FR::FREditorController::Update()
{
	UpdateCurrentEditorMode();

	RenderViews();

	GetService(FREditorActions).ExecuteDelayedActions();

	++mElapsedFrames;
}

void FR::FREditorController::UpdateCurrentEditorMode()
{
	auto editorMode = GetService(FREditorActions).GetCurrentEditorMode();
	if (editorMode == FREditorActions::EEditorMode::PLAY || editorMode == FREditorActions::EEditorMode::FRAME_BY_FRAME)
	{
		UpdatePlayMode();
	}
	else
	{
		UpdateEditMode();
	}

	{
		FRSceneManager::Instance()->GetCurrentScene()->CollectGarbages();
		FRSceneManager::Instance()->Update();
	}
}

void FR::FREditorController::UpdatePlayMode()
{
	auto currentScene = FRSceneManager::Instance()->GetCurrentScene();

	{
		currentScene->Update();
	}

	{
		currentScene->LateUpdate();
	}

	if (GetService(FREditorActions).GetCurrentEditorMode() == FREditorActions::EEditorMode::FRAME_BY_FRAME)
	{
		GetService(FREditorActions).Pause();
	}

	if (FRInput::GetKeyDown(EKeyCode::Esc))
	{
		GetService(FREditorActions).Stop();
	}
}

void FR::FREditorController::UpdateEditMode()
{
	if (FRInput::GetKeyDown(EKeyCode::F5))
	{
		GetService(FREditorActions).Playing();
	}
}

void FR::FREditorController::UpdateEditorPanels()
{
}

void FR::FREditorController::RenderViews()
{
	//assetView->Update();
	sceneView->Update();
	gameView->Update();

	if (sceneRenderer.BeginFrame({}))
	{
		//if (assetView.IsOpened())
		//{
		//	assetView.Render();
		//}

		if (sceneView->IsOpened())
		{
			sceneView->DrawFrame(&sceneRenderer);
		}

		if (gameView->IsOpened())
		{
			gameView->DrawFrame(&sceneRenderer);
		}

		FRApplication::GuiHelper()->Render();

		sceneRenderer.EndFrame();

		{
			//assetView->ResizeRenderTarget();
			sceneView->ResizeRenderTarget();
			gameView->ResizeRenderTarget();
		}
	}
	else
	{
		++mSkippedFrames;
	}
}

void FR::FREditorController::RenderEditorUI()
{
}
