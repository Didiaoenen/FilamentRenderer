#include "AnimationMixerPlayable.h"

#include "Core.FRCompAnimator.h"

#include "SkeletonRig.h"
#include "AnimationMask.h"
#include "AnimationPlayableOutput.h"
#include "PlayableGraph.h"

#include <Log.FRLogger.h>

FR::AnimationMixerPlayable::AnimationMixerPlayable(PlayableGraph* pGraph, uint32_t pMixerCount)
{
	mGraph = pGraph;
	mGraph->AddPlayable(this);

	mLayers.resize(pMixerCount);
	mPlayables.resize(pMixerCount);
}

void FR::AnimationMixerPlayable::SetInputWeight(uint32_t pIndex, float pWeight)
{
    dynamic_cast<AnimationPlayable*>(mPlayables[pIndex])->weight = pWeight;
}

void FR::AnimationMixerPlayable::SetInputCount(uint32_t pInputCount)
{
	mLayers.resize(pInputCount);
	mPlayables.resize(pInputCount);
}

bool FR::AnimationMixerPlayable::InitData()
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
				mLocalTrans.resize(mSkeleton->GetNumSoaJoints());
				isInit = true;
			}
		}
	}
	return isInit;
}

bool FR::AnimationMixerPlayable::Update(float pDeltaTime)
{
	for (const auto& playable : mPlayables)
	{
		if (playable)
		{
			playable->Update(pDeltaTime);
		}
	}

	return true;
}

bool FR::AnimationMixerPlayable::Sample()
{
	InitData();

	for (uint32_t i = 0; i < mPlayables.size(); i++)
	{
		if (auto playable = dynamic_cast<AnimationPlayable*>(mPlayables[i]))
		{
			playable->Sample();
		}
	}

	return Blend();
}

void FR::AnimationMixerPlayable::SetTimeRatio(float pTimeRatio)
{
}

void FR::AnimationMixerPlayable::SetSpeed(float pSpeed)
{
}

float FR::AnimationMixerPlayable::GetDuration()
{
	return 0.0f;
}

void FR::AnimationMixerPlayable::RemovePlayable(uint32_t pIndex)
{
    mPlayables[pIndex] = nullptr;
}

void FR::AnimationMixerPlayable::AddPlayable(APlayable* pPlayable, uint32_t pIndex)
{
	if (auto playable = dynamic_cast<AnimationPlayable*>(pPlayable))
	{
		playable->parent = this;
		mPlayables[pIndex] = playable;
	}
}

void FR::AnimationMixerPlayable::UpdateBlendParameters()
{
}

bool FR::AnimationMixerPlayable::Blend()
{
	auto tempLayers = ozz::vector<ozz::animation::BlendingJob::Layer>();
	for (uint32_t i = 0; i < mPlayables.size(); i++)
	{
		if (auto playable = dynamic_cast<AnimationPlayable*>(mPlayables[i]))
		{
			mLayers[i].transform = make_span(playable->GetLocalTrans());
			mLayers[i].weight = playable->weight;

			if (playable->mask)
			{
				mLayers[i].joint_weights = make_span(playable->mask->GetJointWeights());
			}
			else
			{
				mLayers[i].joint_weights = make_span(ozz::vector<ozz::math::SimdFloat4>());
			}

			tempLayers.emplace_back(mLayers[i]);
		}
	}

	if (mSkeleton)
	{
		ozz::animation::BlendingJob blendJob;
		blendJob.threshold = threshold;
		blendJob.layers = make_span(tempLayers);
		blendJob.output = make_span(mLocalTrans);
		blendJob.rest_pose = mSkeleton->GetJointsRestPoses();

		if (!blendJob.Run())
		{
			FRLogger::Log(std::format("{0} Play Failed", "BlendTree"), FR::FRILogHandler::ELogLevel::LOG_INFO);
			return false;
		}
	}

	return true;
}
