#include "Animation.h"
#include "SkeletonRig.h"
#include "AnimationClip.h"

#include <Log.FRLogger.h>

FR::Animation::Animation(AnimationClip* pClip)
	:clip(pClip)
{
	path = pClip->path;
	name = pClip->GetName();
}

bool FR::Animation::InitData(SkeletonRig* pSeketonRig)
{
	mSkeletonRig = pSeketonRig;

	mLocalTrans.resize(mSkeletonRig->GetNumSoaJoints());

	return true;
}

bool FR::Animation::Update(float pDeltaTime)
{
	float newTime = mTimeRatio;

	if (play)
	{
		newTime = mTimeRatio + pDeltaTime * (playbackSpeed / GetDurtion());
	}

	SetTimeRatio(newTime);

	return true;
}

bool FR::Animation::Sample(float pDeltaTime)
{
	mContext.Resize(mSkeletonRig->GetNumJoints());

	ozz::animation::SamplingJob samplingJob;
	samplingJob.animation = &clip->NativePtr();
	samplingJob.context = &mContext;
	samplingJob.ratio = mTimeRatio;
	samplingJob.output = make_span(mLocalTrans);

	if (!samplingJob.Run())
	{
		FRLogger::Log(std::format("{0} Play Failed", name), FR::FRILogHandler::ELogLevel::LOG_INFO);
		return false;
	}

	return true;
}

float FR::Animation::GetDurtion()
{
	return clip->GetDurtion();
}

void FR::Animation::SetTimeRatio(float pTime)
{
	mPreviousTimeRatio = mTimeRatio;
	if (loop)
	{
		mTimeRatio = pTime - floorf(pTime);
	}
	else
	{
		mTimeRatio = ozz::math::Clamp(0.0f, pTime, 1.0f);
	}
}

float FR::Animation::GetTimeRatio()
{
	return mTimeRatio;
}

float FR::Animation::GetPreviousTimeRatio()
{
	return mPreviousTimeRatio;
}

void FR::Animation::Reset()
{
	mTimeRatio = 0.0f;
	mPreviousTimeRatio = 0.0f;

	play = true;
	loop = false;
	weight = 1.0f;
	playbackSpeed = 1.0f;

	mask = nullptr;
}

FR::Animation::~Animation()
{
}