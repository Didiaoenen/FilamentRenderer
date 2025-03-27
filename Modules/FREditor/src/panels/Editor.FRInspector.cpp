#include "Editor.FRInspector.h"

#include "Editor.FREditorActions.h"

#include <Core.FRActor.h>
#include <Core.FRGuiDrawer.h>
#include <Core.FRCompCamera.h>
#include <Core.FRCompAniTest.h>
#include <Core.FRCompAnimator.h>
#include <Core.FRCompAnimancer.h>
#include <Core.FRCompTransform.h>
#include <Core.FRIInspectorItem.h>
#include <Core.FRCompRendererable.h>

#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

FR::FRInspector::FRInspector(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRPanelWindow(ICON_MDI_INFORMATION " " + pTitle, pOpened, pSettings)
{
	mInspectorHeader = &CreateWidget<FRGroup>();
	{
		mInspectorHeader->enabled = false;
	
		mInspectorHeader->CreateWidget<FRCheckBox>().lineBreak = false;

		mInspectorHeader->CreateWidget<FRText>(ICON_MDI_CUBE).lineBreak = false;

		auto nameGatherer = [this] { return mTargetActor ? mTargetActor->name : "%undef%"; };
		auto nameProvider = [this](const std::string& pNewName) { if (mTargetActor) mTargetActor->name = pNewName; };
		FRGuiDrawer::DrawString(*mInspectorHeader, "Name", nameGatherer, nameProvider);
	}

	mActorInfo = &CreateWidget<FRGroup>();

	auto group = &CreateWidget<FRGroup>();

	mAddComponentWidget = &group->CreateWidget<FRButton>(ICON_MDI_PLUS_BOX_OUTLINE " Add Component");
	{
		mAddComponentWidget->alignment = EWidgetAlignment::CENTER;
		mAddComponentWidget->enabled = false;
		mAddComponentWidget->size.x = 200.f;
	}
		
	auto addComponentPopup = &group->CreateWidget<FRPopup>("AddComponentPopup");
	{
		addComponentPopup->size = { 200.f, 200.f };
		
		auto search = &addComponentPopup->CreateWidget<FRInputText>("");
		search->size = { 184.f, 0.f };

		addComponentPopup->CreateWidget<FRSeparator>();

		auto component = &addComponentPopup->CreateWidget<FRText>("Component");
		component->position = { 64.f, 0.f };

		addComponentPopup->CreateWidget<FRSeparator>();

		auto aniTest = &addComponentPopup->CreateWidget<FRMenuItem>("AniTest");
		aniTest->ClickedEvent += [this] { GetTargetActor()->AddComponent<FRCompAniTest>(); };

		auto animator = &addComponentPopup->CreateWidget<FRMenuItem>("Animator");
		animator->ClickedEvent += [this] { GetTargetActor()->AddComponent<FRCompAnimator>(); };

		auto animancer = &addComponentPopup->CreateWidget<FRMenuItem>("Animancer");
		animancer->ClickedEvent += [this] { GetTargetActor()->AddComponent<FRCompAnimancer>(); };
	}

	mAddComponentWidget->ClickedEvent += [addComponentPopup] { addComponentPopup->OpenPopup(); };

	mInspectorHeader->CreateWidget<FRSeparator>();

	mDestroyedListener = FRActor::DestroyedEvent += [this](FRActor* pDestroyed)
		{
			if (pDestroyed == mTargetActor)
			{
				UnFocus();
			}
		};
}

void FR::FRInspector::FocusActor(FRActor* pTarget)
{
	if (pTarget != mTargetActor)
	{
		UnFocus();

		mTargetActor = pTarget;

		mComponentAddedListener = mTargetActor->ComponentAddedEvent += [this](auto useless)
			{
				GetService(FREditorActions).DelayAction([this] { Refresh(); });
			};
		mComponentRemovedListener = mTargetActor->ComponentRemovedEvent += [this](auto useless)
			{
				GetService(FREditorActions).DelayAction([this] { Refresh(); });
			};

		mInspectorHeader->enabled = true;
		mAddComponentWidget->enabled = true;

		mActorInfo->RemoveAllWidgets();

		CreateActorInspector(pTarget);

		mActorInfo->CreateWidget<FRSeparator>();

		GetService(FREditorActions).ActorSelectedEvent.Invoke(mTargetActor);
	}
}

void FR::FRInspector::UnFocus()
{
	if (mTargetActor)
	{
		mTargetActor->ComponentAddedEvent -= mComponentAddedListener;
		mTargetActor->ComponentRemovedEvent -= mComponentRemovedListener;
	}

	SoftUnFocus();
}

void FR::FRInspector::SoftUnFocus()
{
	if (mTargetActor)
	{
		GetService(FREditorActions).ActorUnselectedEvent.Invoke(mTargetActor);
		mAddComponentWidget->enabled = false;
		mInspectorHeader->enabled = false;
		mTargetActor = nullptr;

		mActorInfo->RemoveAllWidgets();
	}
}

FR::FRActor* FR::FRInspector::GetTargetActor() const
{
	return mTargetActor;
}

void FR::FRInspector::CreateActorInspector(FRActor* pTarget)
{
	std::map<std::string, FRComponent*> components;

	for (auto component : pTarget->GetComponents())
	{
		if (component->GetType() != FRComponent::EComponentType::TRANSFORM)
		{
			components[component->GetName()] = component;
		}
	}

	if (auto transform = pTarget->GetComponent<FRCompTransform>())
	{
		DrawComponent(*transform);
	}

	for (auto& [name, instance] : components)
	{
		DrawComponent(*instance);
	}
}

void FR::FRInspector::DrawComponent(FRComponent& pComponent)
{
	if (auto inspectorItem = dynamic_cast<FRIInspectorItem*>(&pComponent))
	{
		auto& header = mActorInfo->CreateWidget<FRGroupCollapsable>(pComponent.GetName());
		header.closable = !dynamic_cast<FRCompTransform*>(&pComponent);
		header.CloseEvent += [this, &header, &pComponent]
			{
				if (pComponent.owner.RemoveComponent(&pComponent))
				{

				}
			};
		
		inspectorItem->OnInspector(header);
	}
}

void FR::FRInspector::Refresh()
{
	if (mTargetActor)
	{
		mActorInfo->RemoveAllWidgets();
		CreateActorInspector(mTargetActor);
	}
}

FR::FRInspector::~FRInspector()
{
	FRActor::DestroyedEvent -= mDestroyedListener;
}