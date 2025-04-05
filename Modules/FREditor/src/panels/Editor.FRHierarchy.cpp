#include "Editor.FRHierarchy.h"
#include "Editor.FREditorActions.h"

#include <Core.FRActor.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

namespace FR
{
	std::vector<FRTreeNode*> founds;
	std::vector<FRTreeNode*> nodesToCollapse;

	void ExpandTreeNode(FRTreeNode& pToExpand, const FRTreeNode* pRoot)
	{
		pToExpand.Open();

		if (&pToExpand != pRoot && pToExpand.parent)
		{
			ExpandTreeNode(*dynamic_cast<FRTreeNode*>(pToExpand.parent), pRoot);
		}
	}

	void ExpandTreeNodeAndEnable(FRTreeNode& pToExpand, const FRTreeNode* pRoot)
	{
		if (!pToExpand.IsOpened())
		{
			pToExpand.Open();
			nodesToCollapse.push_back(&pToExpand);
		}

		pToExpand.enabled = true;

		if (&pToExpand != pRoot && pToExpand.parent)
		{
			ExpandTreeNodeAndEnable(*dynamic_cast<FRTreeNode*>(pToExpand.parent), pRoot);
		}
	}

	class ActorMenu
		: public FRContextualMenu
	{
	public:
		ActorMenu(FRActor* pTarget, FRTreeNode& pTreeNode)
			: mTarget(pTarget)
			, mTreeNode(pTreeNode)
		{
			if (mTarget)
			{
				auto& focusBtn = CreateWidget<FRMenuItem>("Focus");
				focusBtn.ClickedEvent += [this]
					{
						GetService(FREditorActions).MoveToTarget(mTarget);
					};

				auto& deleteBtn = CreateWidget<FRMenuItem>("Delete");
				deleteBtn.ClickedEvent += [this]
					{
						GetService(FREditorActions).DestroyActor(mTarget);
					};
			}
		}

		virtual void Execute() override
		{
			if (mWidgets.size() > 0)
			{
				FRContextualMenu::Execute();
			}
		}

	private:
		FRActor* mTarget;
		FRTreeNode& mTreeNode;

	};
}

FR::FRHierarchy::FRHierarchy(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRPanelWindow(ICON_MDI_FILE_TREE " " + pTitle, pOpened, pSettings)
{
	auto& searchBar = CreateWidget<FRInputText>();
	{
		searchBar.ContentChangedEvent += std::bind(&FRHierarchy::SearchBarChangedCallback, this, std::placeholders::_1);
	}

	mRoot = &CreateWidget<FRTreeNode>("Root", "", "", true);
	{
		mRoot->Open();
		auto& targetPlugin = mRoot->AddPlugin<FRPluginTarget<ActorNode>>("Actor");
		targetPlugin.DataReceivedEvent += std::bind(&FRHierarchy::RootTargetChangedCallback, this, std::placeholders::_1);
	}

	FRActor::CreatedEvent += std::bind(&FRHierarchy::AddActorByInstance, this, std::placeholders::_1);
	FRActor::DestroyedEvent += std::bind(&FRHierarchy::DeleteActorByInstance, this, std::placeholders::_1);
	
	FRActor::AttachEvent += std::bind(&FRHierarchy::AttachActorToParent, this, std::placeholders::_1);
	FRActor::DettachEvent += std::bind(&FRHierarchy::DetachFromParent, this, std::placeholders::_1);

	GetService(FREditorActions).ActorSelectedEvent += std::bind(&FRHierarchy::SelectActorByInstance, this, std::placeholders::_1);
	GetService(FREditorActions).ActorUnselectedEvent += std::bind(&FRHierarchy::UnselectActorsWidgets, this);
}

void FR::FRHierarchy::UnselectActorsWidgets()
{
	for (auto& widget : mWidgetActorLink)
	{
		widget.second->selected = false;
	}
}

void FR::FRHierarchy::SelectActorByInstance(FRActor* pActor)
{
	if (auto result = mWidgetActorLink.find(pActor); result != mWidgetActorLink.end())
	{
		if (result->second)
		{
			SelectActorByWidget(*result->second);
		}
	}
}

void FR::FRHierarchy::SelectActorByWidget(FRTreeNode& pWidget)
{
	UnselectActorsWidgets();

	pWidget.selected = true;

	if (pWidget.parent)
	{
		ExpandTreeNode(*dynamic_cast<FRTreeNode*>(pWidget.parent), mRoot);
	}
}

void FR::FRHierarchy::AttachActorToParent(FRActor* pActor)
{
	if (auto actorWidget = mWidgetActorLink.find(pActor); actorWidget != mWidgetActorLink.end())
	{
		auto widget = actorWidget->second;

		if (widget->parent)
		{
			widget->parent->UnconsiderWidget(widget);
		}

		if (pActor->HasParent())
		{
			auto parentWidget = mWidgetActorLink[pActor->GetParent()];
			parentWidget->ConsiderWidget(widget);
			parentWidget->leaf = false;
		}
	}
}

void FR::FRHierarchy::DetachFromParent(FRActor* pActor)
{
	if (auto actorWidget = mWidgetActorLink.find(pActor); actorWidget != mWidgetActorLink.end())
	{
		if (pActor->HasParent() && pActor->GetParent()->GetChildren().size() == 1)
		{
			if (auto parentWidget = mWidgetActorLink.find(pActor->GetParent()); parentWidget != mWidgetActorLink.end())
			{
				parentWidget->second->leaf = true;
			}
		}

		auto widget = actorWidget->second;

		if (widget->parent)
		{
			widget->parent->UnconsiderWidget(widget);
		}

		mRoot->ConsiderWidget(widget);
	}
}

void FR::FRHierarchy::AddActorByInstance(FRActor* pActor)
{
	auto& actorSelectable = mRoot->CreateWidget<FRTreeNode>(pActor->name, ICON_MDI_CUBE_OUTLINE, ICON_MDI_CUBE_OUTLINE, true);
	{
		actorSelectable.leaf = true;
		actorSelectable.AddPlugin<ActorMenu>(pActor, actorSelectable);
		actorSelectable.AddPlugin<FRPluginSource<ActorNode>>("Actor", "Attach To...", std::make_pair(pActor, &actorSelectable));
		actorSelectable.AddPlugin<FRPluginTarget<ActorNode>>("Actor").DataReceivedEvent += [this, pActor](ActorNode pElement) { ActorTargetChangedCallback(pElement, pActor); };
		actorSelectable.ClickedEvent += std::bind(&FREditorActions::SelectActor, &GetService(FREditorActions), pActor);
	}

	FRActor* targetPtr = pActor;
	auto& dispatcher = actorSelectable.AddPlugin<FRPluginDispatcher<std::string>>();
	{
		dispatcher.RegisterGatherer([targetPtr] { return targetPtr->name; });
	}

	mWidgetActorLink[targetPtr] = &actorSelectable;
}

void FR::FRHierarchy::DeleteActorByInstance(FRActor* pActor)
{
	if (auto result = mWidgetActorLink.find(pActor); result != mWidgetActorLink.end())
	{
		if (result->second)
		{
			result->second->Destroy();
		}

		if (pActor->HasParent() && pActor->GetParent()->GetChildren().size() == 1)
		{
			if (auto parentWidget = mWidgetActorLink.find(pActor->GetParent()); parentWidget != mWidgetActorLink.end())
			{
				parentWidget->second->leaf = true;
			}
		}

		mWidgetActorLink.erase(result);
	}
}

void FR::FRHierarchy::SearchBarChangedCallback(const std::string& pContent)
{
	founds.clear();
	auto content = pContent;
	std::transform(content.begin(), content.end(), content.begin(), ::tolower);

	for (auto& [actor, item] : mWidgetActorLink)
	{
		if (!pContent.empty())
		{
			auto itemName = item->name;
			std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

			if (itemName.find(content) != std::string::npos)
			{
				founds.push_back(item);
			}

			item->enabled = false;
		}
		else
		{
			item->enabled = true;
		}
	}

	for (auto node : founds)
	{
		node->enabled = true;

		if (node->parent)
		{
			ExpandTreeNodeAndEnable(*dynamic_cast<FRTreeNode*>(node->parent), mRoot);
		}
	}

	if (pContent.empty())
	{
		for (auto node : nodesToCollapse)
		{
			node->Close();
		}

		nodesToCollapse.clear();
	}
}

void FR::FRHierarchy::RootTargetChangedCallback(ActorNode pElement)
{
	if (pElement.second->parent)
	{
		pElement.second->parent->UnconsiderWidget(pElement.second);
	}

	mRoot->ConsiderWidget(pElement.second);

	pElement.first->DetachFromParent();
}

void FR::FRHierarchy::ActorTargetChangedCallback(ActorNode pElement, FRActor* pActor)
{
	if (pActor->IsDescendantOf(pElement.first))
	{
		return;
	}

	pElement.first->SetParent(pActor);
}

FR::FRHierarchy::~FRHierarchy()
{
	mWidgetActorLink.clear();
}
