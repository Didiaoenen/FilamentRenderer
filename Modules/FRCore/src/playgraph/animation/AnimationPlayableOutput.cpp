#include "AnimationPlayableOutput.h"

#include "Core.FRCompAnimator.h"
#include "AnimationPlayable.h"
#include "PlayableGraph.h"

FR::AnimationPlayableOutput::AnimationPlayableOutput(PlayableGraph* pGraph, const std::string& pName, FRCompAnimator* pAnimator)
{
	mGraph = pGraph;
	mGraph->AddOutput(this);

	mAnimator = pAnimator;
}

void FR::AnimationPlayableOutput::SetSourcePlayable(AnimationPlayable* pPlayable)
{
	APlayableOutput::SetSourcePlayable(pPlayable);
	pPlayable->SetOutput(this);
}

void FR::AnimationPlayableOutput::Update(float pDeltaTime)
{
	if (auto playable = dynamic_cast<AnimationPlayable*>(mSourcePlayable))
	{
		mAnimator->GetAnimator().Sample(playable->GetLocalTrans());
	}
}

void FR::AnimationPlayableOutput::SetTarget(FRCompAnimator* pAnimator)
{
	mAnimator = pAnimator;
}

FR::FRCompAnimator* FR::AnimationPlayableOutput::GetTarget() const
{
	return mAnimator;
}
