#pragma once

#include <Core.FRGuiDrawer.h>
#include "Editor.FRAPanelView.h"

namespace FR
{
	class FRScene;
	class FRCamera;

	class FRGameView
		: public FRAPanelView
	{
	public:
		FRGameView(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSettings);

		virtual void Update() override;

		virtual FRCamera* GetCamera();

		virtual FRScene* GetScene();

	private:

	};
}

