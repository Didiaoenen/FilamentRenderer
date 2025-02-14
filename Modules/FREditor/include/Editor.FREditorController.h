#pragma once

#include <Core.FRSceneRenderer.h>
#include "Editor.FREditorActions.h"

namespace FR
{
    class FREditorController
    {
    public:
		FREditorController();

		void Update();

		void SetupUI();

		void UpdateCurrentEditorMode();

		void UpdatePlayMode();

		void UpdateEditMode();

		void UpdateEditorPanels();

		void RenderViews();

		void RenderEditorUI();

	private:
		uint64_t mElapsedFrames{ 0 };
		uint64_t mSkippedFrames{ 0 };

		FRSceneRenderer sceneRenderer;
		FREditorActions editorActions;

    };
}