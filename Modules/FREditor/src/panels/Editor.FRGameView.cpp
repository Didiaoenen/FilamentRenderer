#include "Editor.FRGameView.h"

#include "Editor.FRApplication.h"
#include "Editor.FREditorActions.h"

#include <Core.FRScene.h>
#include <Core.FRCompCamera.h>
#include <Core.FRSceneManager.h>

#include <IconsMaterialDesignIcons.h>

using namespace FR::GUI;

FR::FRGameView::FRGameView(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRAPanelView(ICON_MDI_GAMEPAD_VARIANT " " + pTitle, pOpened, pSettings)
{
	mView.SetName("GameView");
}

void FR::FRGameView::Update()
{
	FRAPanelView::Update();
}

FR::FRCamera* FR::FRGameView::GetCamera()
{
	if (auto scene = FRApplication::SceneManager()->GetCurrentScene())
	{
		if (auto camera = scene->FindMainCamera())
		{
			return &camera->GetCamera();
		}
	}
	return nullptr;
}

FR::FRScene* FR::FRGameView::GetScene()
{
	return FRApplication::SceneManager()->GetCurrentScene();
}
