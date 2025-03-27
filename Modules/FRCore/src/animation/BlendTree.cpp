#include "BlendTree.h"
#include "Animation.h"
#include "SkeletonRig.h"
#include "AnimationMask.h"

#include <Log.FRLogger.h>

FR::BlendTree::BlendTree()
{

}

void FR::BlendTree::AddMotion(AMotion* pMotion)
{
	if (mMotions.size() > 1)
	{
		mMotions.pop_back();
	}
	mMotions.emplace_back(pMotion);

	if (pMotion->additive)
	{
		mNumAdditiveClips++;
	}

	if (pMotion->GetDuration() > mDuration)
	{
		mLongestClipIndex = mMotions.size() - 1;
		mDuration = pMotion->GetDuration();
	}

	mLayers.resize(mMotions.size() - mNumAdditiveClips);
	mAdditiveLayers.resize(mNumAdditiveClips);
}

bool FR::BlendTree::InitData(SkeletonRig* pSkeletonRig)
{
	mSkeletonRig = pSkeletonRig;

	for (const auto& motion : mMotions)
	{
		motion->InitData(pSkeletonRig);
	}

	mLocalTrans.resize(mSkeletonRig->GetNumSoaJoints());

	return true;
}

bool FR::BlendTree::Update(float pDeltaTime)
{
	auto step = 1 / (5 / pDeltaTime);

	for (const auto& motion : mMotions)
	{
		motion->Update(pDeltaTime);

		if (mMotions.size() > 1)
		{
			if (motion == mMotions[0])
			{
				mMotions[0]->weight = ozz::math::Clamp(0.0f, mMotions[0]->weight -= step, 1.0f);
			}
			else
			{
				mMotions[1]->weight = ozz::math::Clamp(0.0f, mMotions[1]->weight += step, 1.0f);
			}
		}
	}

	//auto step = 1 / (0.1 / (1 / pDeltaTime));
	//mMotions[0]->weight = ozz::math::Clamp(0.0f, mMotions[0]->weight -= step, 1.0f);
	//mMotions[1]->weight = ozz::math::Clamp(0.0f, mMotions[1]->weight += step, 1.0f);

	return true;
}

bool FR::BlendTree::Sample(float pDeltaTime)
{
	if (autoSetBlendParams)
	{
		UpdateBlendParameters();
	}

	for (const auto& motion : mMotions)
	{
		if (motion->weight > 0.0f)
		{
			if (!motion->Sample(pDeltaTime))
			{
				return false;
			}
		}
	}

	if (mMotions.size() > 0 && mMotions[mLongestClipIndex])
	{
		mTimeRatio = mMotions[mLongestClipIndex]->GetTimeRatio();
	}

	return Blend();
}

void FR::BlendTree::SetTimeRatio(float pTimeRatio)
{
	mTimeRatio = pTimeRatio;

	for (const auto& motion : mMotions)
	{
		motion->SetTimeRatio(pTimeRatio * mDuration);
	}
}

float FR::BlendTree::GetTimeRatio()
{
	return mTimeRatio;
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
		for (uint32_t i = 0; i < mMotions.size(); i++)
		{
			mMotions[i]->weight = 1.f / mMotions.size();
		}
	}
	else if (blendType == EBlendType::CROSS_DISSOLVE)
	{
		const float numIntervals = (float)mMotions.size() - 1;
		const float interval = 1.f / numIntervals;
		for (uint32_t i = 0; i < mMotions.size(); i++)
		{
			const float med = i * interval;
			const float x = blendRatio - med;
			const float y = ((x < 0.f ? x : -x) + interval) * numIntervals;

			mMotions[i]->weight = std::max(0.f, y);
		}
	}
	else if (blendType == EBlendType::CROSS_DISSOLVE_SYNC)
	{
		const float numIntervals = (float)mMotions.size() - 1;
		const float interval = 1.f / numIntervals;
		for (uint32_t i = 0; i < mMotions.size(); i++)
		{
			const float med = i * interval;
			const float x = blendRatio - med;
			const float y = ((x < 0.f ? x : -x) + interval) * numIntervals;

			mMotions[i]->weight = std::max(0.f, y);
		}

		const uint32_t relevantClip = static_cast<uint32_t>((blendRatio - 1e-3f) * (mMotions.size() - 1));
		const float loopDuration = mMotions[relevantClip]->GetDuration() * mMotions[relevantClip]->weight + mMotions[relevantClip + 1]->GetDuration() * mMotions[relevantClip + 1]->weight;

		const float invLoopDuration = 1.f / loopDuration;
		for (uint32_t i = 0; i < mMotions.size(); i++)
		{
			mMotions[i]->playbackSpeed = mMotions[i]->GetDuration() * invLoopDuration;
		}
	}
}

bool FR::BlendTree::Blend()
{
	uint32_t additiveIndex = 0;
	for (uint32_t i = 0; i < mMotions.size(); i++)
	{
		if (mMotions[i]->additive)
		{
			mAdditiveLayers[additiveIndex].transform = make_span(mMotions[i]->GetLocalTrans());
			mAdditiveLayers[additiveIndex].weight = mMotions[i]->weight;

			if (mMotions[i]->mask)
			{
				mAdditiveLayers[additiveIndex].joint_weights = make_span(mMotions[i]->mask->GetJointWeights());
			}
			else
			{
				mAdditiveLayers[additiveIndex].joint_weights = make_span(ozz::vector<ozz::math::SimdFloat4>());
			}

			additiveIndex++;
		}
		else
		{
			mLayers[i].transform = make_span(mMotions[i]->GetLocalTrans());
			mLayers[i].weight = mMotions[i]->weight;

			if (mMotions[i]->mask)
			{
				mLayers[i].joint_weights = make_span(mMotions[i]->mask->GetJointWeights());
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