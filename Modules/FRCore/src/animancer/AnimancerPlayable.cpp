#include "AnimancerPlayable.h"

#include "Animator.h"
#include "AnimancerNode.h"
#include "AnimancerState.h"
#include "AnimancerLayer.h"

#include "PlayableGraph.h"
#include "AnimationBasePlayable.h"
#include "AnimationPlayableOutput.h"

#include <algorithm>

FR::AnimancerPlayable::AnimancerPlayable()
	: mGraph(new PlayableGraph()), mRootPlayable(new AnimationBasePlayable(mGraph, 1))
	, layers(this, mPlayable)
	, states(this)
{
}

FR::PlayableGraph* FR::AnimancerPlayable::Graph()
{
	return mGraph;
}

FR::AnimationPlayable* FR::AnimancerPlayable::Playable()
{
	return mPlayable;
}

FR::IPlayableWarp* FR::AnimancerPlayable::Parent()
{
	return nullptr;
}

float FR::AnimancerPlayable::Weight()
{
	return mWeight;
}

void FR::AnimancerPlayable::SetWeight(float pWeight)
{
	mWeight = pWeight;
}

float FR::AnimancerPlayable::Speed()
{
	return mSpeed;
}

void FR::AnimancerPlayable::SetSpeed(float pSpeed)
{
	mSpeed = pSpeed;
}

void FR::AnimancerPlayable::CreateOutput(FRCompAnimator* pAnimator)
{
	mOutput = new AnimationPlayableOutput(mGraph, "output", pAnimator);
	mOutput->SetSourcePlayable(mRootPlayable);
	mGraph->Play();

	mIsGraphPlaying = true;
}

std::any FR::AnimancerPlayable::GetKey(AnimationClip* pClip)
{
	return pClip;
}

FR::AnimancerState* FR::AnimancerPlayable::Play(AnimationClip* pClip)
{
	return Play(states.GetOrCreate(pClip));
}

FR::AnimancerState* FR::AnimancerPlayable::Play(AnimancerState* pState)
{
	return GetLocalLayer(pState)->Play(pState);
}

FR::AnimancerState* FR::AnimancerPlayable::Play(AnimationClip* pClip, float pFadeDuration)
{
	return Play(states.GetOrCreate(pClip), pFadeDuration);
}

FR::AnimancerState* FR::AnimancerPlayable::Play(AnimancerState* pState, float pFadeDuration)
{
	return GetLocalLayer(pState)->Play(pState, pFadeDuration);
}

void FR::AnimancerPlayable::Stop()
{
}

bool FR::AnimancerPlayable::IsPlaying()
{
	return false;
}

bool FR::AnimancerPlayable::IsPlayingClip(AnimationClip* pClip)
{
	return false;
}

void FR::AnimancerPlayable::RequirePreUpdate(IUpdatable* pUpdateble)
{
	auto find = std::find(mPreUpdatables.begin(), mPreUpdatables.end(), pUpdateble);
	if (find != mPreUpdatables.end())
	{
		return;
	}

	mPreUpdatables.emplace_back(pUpdateble);
}

void FR::AnimancerPlayable::RequirePostUpdate(IUpdatable* pUpdateble)
{
}

void FR::AnimancerPlayable::CancelPreUpdate(IUpdatable* pUpdateble)
{
	CancelUpdate(mPreUpdatables, pUpdateble);
}

void FR::AnimancerPlayable::CancelPostUpdate(IUpdatable* pUpdateble)
{
}

void FR::AnimancerPlayable::PrepareFrame(float pDeltaTime)
{
	UpdateAll(mPreUpdatables, pDeltaTime);
}

void FR::AnimancerPlayable::SetGraphPlaying(bool pIsPlaying)
{
	if (pIsPlaying)
	{
		if (!mIsGraphPlaying)
		{
			mGraph->Play();
			mIsGraphPlaying = true;
		}
	}
	else
	{
		if (mIsGraphPlaying)
		{
			mGraph->Stop();
			mIsGraphPlaying = false;
		}
	}
}

FR::AnimancerLayer* FR::AnimancerPlayable::GetLocalLayer(AnimancerState* pState)
{
	if (pState->Root() == this)
	{
		if (auto layer = pState->Layer())
		{
			return layer;
		}
	}

	return layers[0];
}

void FR::AnimancerPlayable::CancelUpdate(std::vector<IUpdatable*>& pUpdateables, IUpdatable* pUpdateable)
{
	auto find = std::find(pUpdateables.begin(), pUpdateables.end(), pUpdateable);
	if (find == pUpdateables.end())
	{
		return;
	}
		
	auto index = std::distance(pUpdateables.begin(), find);

	pUpdateables.erase(find);

	if (mUpdateableCount < index && pUpdateables == mCurrUpdatables)
	{
		mUpdateableCount--;
	}
}

void FR::AnimancerPlayable::UpdateAll(std::vector<IUpdatable*> pUpdateables, float pDeltaTime)
{
	auto previous = current;
	current = this;

	auto preUpdatables = mCurrUpdatables;
	mCurrUpdatables = pUpdateables;

	deltaTime = pDeltaTime;

	auto preUpdateCount = mUpdateableCount;
	mUpdateableCount = pUpdateables.size();

	while (--mUpdateableCount >= 0)
	{
		pUpdateables[mUpdateableCount]->Update();
	}

	mUpdateableCount = preUpdateCount;
	mCurrUpdatables = preUpdatables;

	current = previous;
}

FR::AnimancerPlayable::~AnimancerPlayable()
{
	delete mGraph; mGraph = nullptr;
	delete mOutput; mOutput = nullptr;
}
