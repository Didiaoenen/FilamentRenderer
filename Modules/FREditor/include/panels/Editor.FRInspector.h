#pragma once

#include <Core.FRGuiDrawer.h>
#include <GUI.FRPanelWindow.h>

namespace FR
{
	class FRActor;
	class FRComponent;

	class FRInspector
		: public GUI::FRPanelWindow
	{
	public:
		FRInspector(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSettings);

		void FocusActor(FRActor* pTarget);

		void UnFocus();

		void SoftUnFocus();

		FRActor* GetTargetActor() const;

		void CreateActorInspector(FRActor* pTarget);

		void DrawComponent(FRComponent& pComponent);

		void Refresh();

	public:
		~FRInspector();

	private:
		FRActor* mTargetActor{ nullptr };
		GUI::FRGroup* mActorInfo;
		GUI::FRGroup* mInspectorHeader;
		GUI::FRButton* mAddComponentWidget;

		uint64_t mDestroyedListener = 0;
		uint64_t mComponentAddedListener = 0;
		uint64_t mComponentRemovedListener = 0;

	};
}

