#include "Core.FRCompAnimancer.h"
#include "Core.FROzzAnimationManager.h"

#include "Core.FRActor.h"
#include "Core.FRGuiDrawer.h"
#include "Core.FRCompAnimator.h"

#include "AnimationClip.h"

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

FR::FRCompAnimancer::FRCompAnimancer(FRActor& pOwner)
	: FRComponent(pOwner)
{
}

void FR::FRCompAnimancer::OnStart()
{
	if (auto animator = owner.GetComponent<FRCompAnimator>())
	{
		mPlayable.CreateOutput(animator);
	}
}

void FR::FRCompAnimancer::OnUpdate(float pDeltaTime)
{
	mPlayable.PrepareFrame(pDeltaTime);
}

void FR::FRCompAnimancer::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompAnimancer::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompAnimancer::OnInspector(GUI::FRWidgetContainer& pRoot)
{
}

const std::string FR::FRCompAnimancer::GetName()
{
	return ICON_MDI_MERGE " Animancer";
}

FR::FRComponent::EComponentType FR::FRCompAnimancer::GetType()
{
	return EComponentType();
}

FR::AnimancerState* FR::FRCompAnimancer::Play(AnimationClip* pClip)
{
	return mPlayable.Play(pClip);
}

FR::AnimancerState* FR::FRCompAnimancer::Play(AnimationClip* pClip, float pFadeDuration)
{
	return mPlayable.Play(pClip, pFadeDuration);
}

FR::FRCompAnimancer::~FRCompAnimancer()
{
}
