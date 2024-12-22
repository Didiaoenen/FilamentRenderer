#include "BlendTree.h"
#include "Animation.h"
#include "SkeletonRig.h"
#include "AnimationMask.h"

#include <Log.FRLogger.h>

FR::BlendTree::BlendTree(ozz::vector<Animation*> pClips)
{
	mClips = std::move(pClips);

	for (uint32_t i = 0; i < mClips.size(); i++)
	{
		if (mClips[i]->additive)
		{
			mNumAdditiveClips++;
		}

		if (mClips[i]->GetDurtion() > mDuration)
		{
			mLongestClipIndex = i;
			mDuration = mClips[i]->GetDurtion();
		}
	}

	mLayers.resize(mClips.size() - mNumAdditiveClips);
	mAdditiveLayers.resize(mNumAdditiveClips);
}

bool FR::BlendTree::InitData(SkeletonRig* pSkeletonRig)
{
	mSkeletonRig = pSkeletonRig;

	for (const auto& clip : mClips)
	{
		clip->InitData(pSkeletonRig);
	}

	mLocalTrans.resize(mSkeletonRig->GetNumSoaJoints());

	return true;
}

bool FR::BlendTree::Update(float pDeltaTime)
{
	for (const auto& clip : mClips)
	{
		clip->Update(pDeltaTime);
	}

	return true;
}

bool FR::BlendTree::Sample(float pDeltaTime)
{
	if (autoSetBlendParams)
	{
		UpdateBlendParameters();
	}

	for (const auto& clip : mClips)
	{
		if (clip->weight > 0.0f)
		{
			if (!clip->Sample(pDeltaTime))
			{
				return false;
			}
		}
	}

	mTimeRatio = mClips[mLongestClipIndex]->GetTimeRatio();

	return Blend();
}

void FR::BlendTree::SetTimeRatio(float pTimeRatio)
{
	mTimeRatio = pTimeRatio;

	for (const auto& clip : mClips)
	{
		clip->SetTimeRatio(pTimeRatio * mDuration);
	}
}

float FR::BlendTree::GetDuration()
{
	return mDuration;
}

void FR::BlendTree::UpdateBlendParameters()
{
	threshold = ozz::animation::BlendingJob().threshold;

	if (blendType == EBlendType::EQUAL)
	{
		for (uint32_t i = 0; i < mClips.size(); i++)
		{
			mClips[i]->weight = 1.f / mClips.size();
		}
	}
	else if (blendType == EBlendType::CROSS_DISSOLVE)
	{
		const float numIntervals = (float)mClips.size() - 1;
		const float interval = 1.f / numIntervals;
		for (uint32_t i = 0; i < mClips.size(); i++)
		{
			const float med = i * interval;
			const float x = blendRatio - med;
			const float y = ((x < 0.f ? x : -x) + interval) * numIntervals;

			mClips[i]->weight = std::max(0.f, y);
		}
	}
	else if (blendType == EBlendType::CROSS_DISSOLVE_SYNC)
	{
		const float numIntervals = (float)mClips.size() - 1;
		const float interval = 1.f / numIntervals;
		for (uint32_t i = 0; i < mClips.size(); i++)
		{
			const float med = i * interval;
			const float x = blendRatio - med;
			const float y = ((x < 0.f ? x : -x) + interval) * numIntervals;

			mClips[i]->weight = std::max(0.f, y);
		}

		const uint32_t relevantClip = static_cast<uint32_t>((blendRatio - 1e-3f) * (mClips.size() - 1));
		const float loopDuration = mClips[relevantClip]->GetDurtion() * mClips[relevantClip]->weight + mClips[relevantClip + 1]->GetDurtion() * mClips[relevantClip + 1]->weight;

		const float invLoopDuration = 1.f / loopDuration;
		for (uint32_t i = 0; i < mClips.size(); i++)
		{
			mClips[i]->playbackSpeed = mClips[i]->GetDurtion() * invLoopDuration;
		}
	}
}

bool FR::BlendTree::Blend()
{
	uint32_t additiveIndex = 0;
	for (uint32_t i = 0; i < mClips.size(); i++)
	{
		if (mClips[i]->additive)
		{
			mAdditiveLayers[additiveIndex].transform = make_span(mClips[i]->GetLocalTrans());
			mAdditiveLayers[additiveIndex].weight = mClips[i]->weight;

			if (mClips[i]->mask)
			{
				mAdditiveLayers[additiveIndex].joint_weights = make_span(mClips[i]->mask->GetJointWeights());
			}
			else
			{
				mAdditiveLayers[additiveIndex].joint_weights = make_span(ozz::vector<ozz::math::SimdFloat4>());
			}

			additiveIndex++;
		}
		else
		{
			mLayers[i].transform = make_span(mClips[i]->GetLocalTrans());
			mLayers[i].weight = mClips[i]->weight;

			if (mClips[i]->mask)
			{
				mLayers[i].joint_weights = make_span(mClips[i]->mask->GetJointWeights());
			}
			else
			{
				mLayers[i].joint_weights = make_span(ozz::vector<ozz::math::SimdFloat4>());
			}
		}
	}

	ozz::animation::BlendingJob blendJob;
	blendJob.threshold = threshold;
	blendJob.layers = make_span(mLayers);
	blendJob.output = make_span(mLocalTrans);
	blendJob.rest_pose = mSkeletonRig->GetJointsRestPoses();

	if (mNumAdditiveClips > 0)
	{
		blendJob.additive_layers = make_span(mAdditiveLayers);
	}

	if (!blendJob.Run())
	{
		FRLogger::Log(std::format("{0} Play Failed", "BlendTree"), FR::FRILogHandler::ELogLevel::LOG_INFO);
		return false;
	}

	return true;
}