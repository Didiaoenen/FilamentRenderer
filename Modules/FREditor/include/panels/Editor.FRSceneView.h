#pragma once

#include <imgui.h>
#include <ImGuizmo.h>
#include "Editor.FRAViewController.h"

namespace FR
{
	class FRScene;

	class FRSceneView
		: public FRAViewController
	{
	public:
		FRSceneView(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSetting);

		virtual void Update() override;

		virtual FRScene* GetScene();

	private:
		ImGuizmo::OPERATION mCurrentOperation{ ImGuizmo::OPERATION::TRANSLATE };

		FROptRef<FRActor> mHighlightedActor;

	protected:
		virtual void DrawGizmo() override;
	
		void HandleActorPicking();

	};
}

