#include "AnimancerState.h"

#include "APlayable.h"
#include "AnimancerPlayable.h"
#include "AnimancerPlayable.StateMap.h"
#include "AnimationClipPlayable.h"

FR::AnimancerState::AnimancerState(AnimationClip* pClip)
{
	mClip = pClip;
}

void FR::AnimancerState::SetRoot(AnimancerPlayable* pRoot)
{
	if (mRoot == pRoot)
	{
		return;
	}

	if (mRoot)
	{
		mRoot->CancelPreUpdate(this);
		mRoot->states.Unregister(this);

		if (mParent && mParent->Root() != pRoot)
		{
			mParent->OnRemoveChild(this);
			mParent = nullptr;
		}

		DestroyPlayable();
	}

	mRoot = pRoot;

	if (mRoot)
	{
		mRoot->states.Register(this);

		CreatePlayable();
	}
}

FR::IPlayableWarp* FR::AnimancerState::Parent()
{
	return mParent;
}

void FR::AnimancerState::SetParent(AnimancerNode* pParent, int pIndex)
{
	if (mParent)
	{
		mParent->OnRemoveChild(this);
		mParent = nullptr;
	}

	if (!pParent)
	{
		return;
	}

	SetRoot(pParent->Root());

	mIndex = pIndex;
	mParent = pParent;
	mParent->OnAddChild(this);
}

void FR::AnimancerState::SetParentInternal(AnimancerNode* pParent, int pIndex)
{
	mIndex = pIndex;
	mParent = pParent;
}

FR::AnimancerLayer* FR::AnimancerState::Layer()
{
	return mParent ? mParent->Layer() : nullptr;
}

std::any FR::AnimancerState::Key()
{
	return mKey;
}

void FR::AnimancerState::SetKey(std::any pAny)
{
	if (!mRoot)
	{
		mKey = pAny;
	}
	else
	{
		mRoot->states.Unregister(this);
		mKey = pAny;
		mRoot->states.Register(this);
	}
}

FR::AnimationClip* FR::AnimancerState::Clip()
{
	return mClip;
}

void FR::AnimancerState::SetClip(AnimationClip* pClip)
{
	if (std::any_cast<AnimationClip*>(mKey) == mClip)
	{
		mKey = pClip;
	}

	mClip = pClip;
}

bool FR::AnimancerState::IsPlaying()
{
	return mIsPlaying;
}

void FR::AnimancerState::SetPlaying(bool pPlay)
{
	if (mIsPlaying == pPlay)
	{
		return;
	}

	mIsPlaying = pPlay;

	if (mIsPlayingDirty)
	{
		mIsPlayingDirty = false;
	}
	else
	{
		mIsPlayingDirty = true;
		RequireUpdate();
	}

	OnSetIsPlaying();
}

void FR::AnimancerState::CreatePlayable()
{
	AnimancerNode::CreatePlayable();

	if (!mIsPlaying)
	{
		mPlayable->Pause();
	}

	mIsPlayingDirty = false;
}

void FR::AnimancerState::CreatePlayable(AnimationPlayable*& pPlayable)
{
	pPlayable = new AnimationClipPlayable(Root()->Graph(), mClip);
}

void FR::AnimancerState::Play()
{
	SetPlaying(true);
	SetWeight(1.f);
}

void FR::AnimancerState::Stop()
{
	AnimancerNode::Stop();
	mIsPlaying = false;
}

void FR::AnimancerState::OnStartFade()
{
}

FR::AnimancerState* FR::AnimancerState::Clone()
{
	return Clone(mRoot);
}

FR::AnimancerState* FR::AnimancerState::Clone(AnimancerPlayable* pRoot)
{
	auto clone = new AnimancerState();
	clone->SetNewCloneRoot(pRoot);
	clone->CopyFrom(this);
	return clone;
}

void FR::AnimancerState::CopyFrom(AnimancerState* pState)
{
	AnimancerNode::CopyFrom(pState);
}

void FR::AnimancerState::Update(bool& pNeedsMoreUpdates)
{
	AnimancerNode::Update(pNeedsMoreUpdates);

	if (mIsPlayingDirty)
	{
		mIsPlayingDirty = false;

		// TODO
		if (mIsPlaying)
		{
            mPlayable->Play();
		}
		else
		{
			mPlayable->Pause();
		}
	}
}

void FR::AnimancerState::SetNewCloneRoot(AnimancerPlayable* pRoot)
{
	if (!mRoot)
	{
		return;
	}

	mRoot = pRoot;
}

FR::AnimancerState::~AnimancerState()
{
}
