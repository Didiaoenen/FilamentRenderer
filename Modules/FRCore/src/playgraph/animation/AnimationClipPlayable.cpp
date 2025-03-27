#include "AnimationClipPlayable.h"

#include "Core.FRCompAnimator.h"

#include "SkeletonRig.h"
#include "AnimationClip.h"
#include "AnimationPlayableOutput.h"
#include "PlayableGraph.h"

#include <Log.FRLogger.h>

FR::AnimationClipPlayable::AnimationClipPlayable(PlayableGraph* pGraph, AnimationClip* pClip)
{
	mGraph = pGraph;
	mGraph->AddPlayable(this);

	mClip = pClip;
	name = pClip->GetName();
}

bool FR::AnimationClipPlayable::Update(float pDeltaTime)
{
	float newTime = mTimeRatio;

	if (play)
	{
		newTime = mTimeRatio + pDeltaTime * (mSpeed / GetDuration());
	}

	SetTimeRatio(newTime);

	return true;
}

bool FR::AnimationClipPlayable::InitData()
{
	if (!isInit)
	{
		auto output = GetOutput();
		if (auto root = GetRootPlayable())
		{
			output = root->GetOutput();
		}

		if (output)
		{
			auto target = output->GetTarget();
			if (mSkeleton = target->GetAnimator().GetSkeletonRig())
			{
				mContext.Resize(mSkeleton->GetNumJoints());
				mLocalTrans.resize(mSkeleton->GetNumSoaJoints());
				isInit = true;
			}
		}
	}
	return isInit;
}

bool FR::AnimationClipPlayable::Sample()
{
	InitData();

	ozz::animation::SamplingJob samplingJob;
	samplingJob.ratio = mTimeRatio;
	samplingJob.context = &mContext;
	samplingJob.animation = &mClip->NativePtr();
	samplingJob.output = make_span(mLocalTrans);

	if (!samplingJob.Run())
	{
		FRLogger::Log(std::format("{0} Play Failed", name), FR::FRILogHandler::ELogLevel::LOG_INFO);
		return false;
	}

	return true;
}

void FR::AnimationClipPlayable::SetTimeRatio(float pTime)
{
	if (loop)
	{
		mTimeRatio = pTime - floorf(pTime);
	}
	else
	{
		mTimeRatio = ozz::math::Clamp(0.f, pTime, 1.f);
		if (mTimeRatio >= 1.f)
		{
			weight = 0.f;
		}
	}
}

void FR::AnimationClipPlayable::SetSpeed(float pSpeed)
{
	mSpeed = pSpeed;
}

float FR::AnimationClipPlayable::GetDuration()
{
	return mClip->GetDuration();
}

void FR::AnimationClipPlayable::Reset()
{
}
