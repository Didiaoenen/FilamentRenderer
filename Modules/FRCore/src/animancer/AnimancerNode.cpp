#include "AnimancerNode.h"

#include "AnimancerState.h"
#include "AnimancerPlayable.h"

#include "AnimationPlayable.h"
#include "APlayableParent.h"
#include "PlayableGraph.h"

#include <Log.FRLogger.h>

#include <glm/ext.hpp>

FR::AnimationPlayable* FR::AnimancerNode::Playable()
{
	return mPlayable;
}

void FR::AnimancerNode::CreatePlayable()
{
	CreatePlayable(mPlayable);

	if (mSpeed != 1.f)
	{
		mPlayable->SetSpeed(mSpeed);
	}

	if (auto parent = Parent())
	{
		ApplyConnectedState(parent);
	}
}

void FR::AnimancerNode::DestroyPlayable()
{
	Root()->Graph()->DestroyPlayable(mPlayable);
}

void FR::AnimancerNode::RecreatePlayable()
{
}

void FR::AnimancerNode::CopyFrom(AnimancerNode* pCopyFrom)
{
	mWeight = pCopyFrom->mWeight;
	mIsWeightDirty = true;

	targetWeight = pCopyFrom->targetWeight;
	fadeSpeed = pCopyFrom->fadeSpeed;

	SetSpeed(pCopyFrom->Speed());
}

FR::AnimancerPlayable* FR::AnimancerNode::Root()
{
	return mRoot;
}

void FR::AnimancerNode::SetRoot(AnimancerPlayable* pRoot)
{
	mRoot = pRoot;
}

FR::AnimancerLayer* FR::AnimancerNode::Layer()
{
	return nullptr;
}

FR::IPlayableWarp* FR::AnimancerNode::Parent()
{
	return mParent;
}

int FR::AnimancerNode::Index()
{
	return mIndex;
}

void FR::AnimancerNode::Update()
{
	bool needsMoreUpdates;
	Update(needsMoreUpdates);
	if (needsMoreUpdates)
	{
		return;
	}

	mRoot->CancelPreUpdate(this);
}

FR::AnimancerState* FR::AnimancerNode::GetChild()
{
	return nullptr;
}

float FR::AnimancerNode::Weight()
{
	return mWeight;
}

void FR::AnimancerNode::SetWeight(float pWeight)
{
	if (mWeight != pWeight)
	{
		mWeight = pWeight;
		SetWeightDirty();
	}

	targetWeight = pWeight;
	fadeSpeed = 0.0f;
}

void FR::AnimancerNode::ApplyWeight()
{
	if (!mIsWeightDirty)
	{
		return;
	}

	mIsWeightDirty = false;

	auto parent = Parent();

	if (!parent)
	{
		return;
	}

	if (mWeight == 0.f)
	{
		DisconnectFromGraph();
		return;
	}

	ConnectToGraph();

	if (auto parentPlayable = dynamic_cast<APlayableParent*>(parent->Playable()))
	{
		parentPlayable->SetInputWeight(Index(), mWeight);
	}
}

void FR::AnimancerNode::StartFade(float pTargetWeight)
{
	StartFade(pTargetWeight, AnimancerPlayable::defaultFadeDuration);
}

void FR::AnimancerNode::StartFade(float pTargetWeight, float pFadeDuration)
{
	targetWeight = pTargetWeight;

	if (targetWeight == mWeight)
	{
		if (targetWeight == 0.f)
		{
			Stop();
		}
		else
		{
			fadeSpeed = 0.f;
			OnStartFade();
		}

		return;
	}

	if (pFadeDuration <= 0.f)
	{
		fadeSpeed = 0.f;
	}
	else
	{
		fadeSpeed = glm::abs(mWeight - targetWeight) / pFadeDuration;
	}

	OnStartFade();
	RequireUpdate();
}

void FR::AnimancerNode::Stop()
{
	SetWeight(0.f);
}

float FR::AnimancerNode::Speed()
{
	return mSpeed;
}

void FR::AnimancerNode::SetSpeed(float pSpeed)
{
	if (mSpeed == pSpeed)
	{
		return;
	}

	mSpeed = pSpeed;
    mPlayable->SetSpeed(pSpeed);
}

void FR::AnimancerNode::RequireUpdate()
{
	if (mRoot)
	{
		mRoot->RequirePreUpdate(this);
	}
}

void FR::AnimancerNode::Update(bool& pNeedsMoreUpdates)
{
	UpdateFade(pNeedsMoreUpdates);
	ApplyWeight();
}

void FR::AnimancerNode::OnAddChild(std::vector<AnimancerState*>& pStates, AnimancerState* pState)
{
	if (auto find = std::find(pStates.begin(), pStates.end(), pState); find != pStates.end())
	{
		pState->SetParentInternal(nullptr);
	}

	pStates.emplace_back(pState);

	if (mRoot)
	{
		pState->ApplyConnectedState(this);
	}
}

void FR::AnimancerNode::SetWeightDirty()
{
	mIsWeightDirty = true;
	RequireUpdate();
}

void FR::AnimancerNode::ConnectToGraph()
{
	auto parent = Parent();

	if (!parent)
	{
		return;
	}

	auto playable = parent->Playable();
	auto parentPlayable = dynamic_cast<APlayableParent*>(playable);
	Root()->Graph()->Connect(mPlayable, 0, parentPlayable, Index());
	parentPlayable->SetInputWeight(Index(), mWeight);

	mIsWeightDirty = false;
}

void FR::AnimancerNode::DisconnectFromGraph()
{
	auto parent = Parent();

	if (!parent)
	{
		return;
	}

	auto playable = parent->Playable();
	auto parentPlayable = dynamic_cast<APlayableParent*>(playable);
	Root()->Graph()->Disconnect(parentPlayable, Index());
}

void FR::AnimancerNode::ApplyConnectedState(IPlayableWarp* pParent)
{
	mIsWeightDirty = true;

	if (mWeight != 0.f)
	{
		ConnectToGraph();
	}
	else
	{
		mRoot->RequirePreUpdate(this);
	}
}

void FR::AnimancerNode::UpdateFade(bool& pNeedsMoreUpdates)
{
	auto tFadeSpeed = fadeSpeed;

	if (tFadeSpeed == 0)
	{
		pNeedsMoreUpdates = false;
		return;
	}

	mIsWeightDirty = true;

	tFadeSpeed *= ParentEffectiveSpeed() * AnimancerPlayable::deltaTime;
	if (tFadeSpeed < 0.f)
	{
		tFadeSpeed *= -1;
	}

	auto target = targetWeight;
	auto current = mWeight;

	auto delta = target - current;
	if (delta > 0)
	{
		if (delta > tFadeSpeed)
		{
			mWeight = current + tFadeSpeed;
			pNeedsMoreUpdates = true;
			return;
		}
	}
	else
	{
		if (-delta > tFadeSpeed)
		{
			mWeight = current - tFadeSpeed;
			pNeedsMoreUpdates = true;
			return;
		}
	}

	mWeight = target;
	pNeedsMoreUpdates = false;

	if (target == 0.f)
	{
		Stop();
	}
	else
	{
		fadeSpeed = 0.f;
	}
}

float FR::AnimancerNode::ParentEffectiveSpeed()
{
	return 1.f;
}
