#pragma once

#include <algorithm>
#include <unordered_map>
#include <Core.FRGuiDrawer.h>
#include <GUI.FRPanelWindow.h>

namespace FR
{
	class FRActor;

	class FRHierarchy
		: public GUI::FRPanelWindow
	{
		using ActorNode = std::pair<FRActor*, GUI::FRTreeNode*>;

	public:
		FRHierarchy(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSetting);

		void UnselectActorsWidgets();

		void SelectActorByInstance(FRActor& pActor);

		void SelectActorByWidget(GUI::FRTreeNode& pWidget);

		void AttachActorToParent(FRActor& pActor);

		void DetachFromParent(FRActor& pActor);

		void AddActorByInstance(FRActor& pActor);

		void DeleteActorByInstance(FRActor& pActor);

	private:
		void SearchBarChangedCallback(const std::string& pContent);

		void RootTargetChangedCallback(ActorNode pElement);

		void ActorTargetChangedCallback(ActorNode pElement, FRActor& pActor);

	public:
		virtual ~FRHierarchy() = default;

	public:
		FREvent<FRActor&> ActorSelectedEvent;
		FREvent<FRActor&> ActorUnselectedEvent;

	private:
		GUI::FRTreeNode* mRoot;
		std::unordered_map<FRActor*, GUI::FRTreeNode*> mWidgetActorLink;

	};
}

