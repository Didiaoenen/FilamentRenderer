#include "AnimancerPlayable.LayerVec.h"

#include "AnimancerLayer.h"
#include "AnimancerPlayable.h"
#include "AnimationLayerPlayable.h"
#include "AnimationBasePlayable.h"
#include "APlayableParent.h"
#include "PlayableGraph.h"

FR::LayerVec::LayerVec(AnimancerPlayable* pRoot, AnimationPlayable*& pPlayable)
{
	root = pRoot;
	mLayers.resize(LayerVec::defaultCapacity);
	pPlayable = new AnimationLayerPlayable(pRoot->Graph(), 1);
	root->Graph()->Connect(pPlayable, 0, pRoot->mRootPlayable, 0);
}

FR::AnimancerLayer* FR::LayerVec::GetLayer(int pIndex)
{
	return mLayers[pIndex];
}

void FR::LayerVec::SetCapacity(int pCapacity)
{
	if (mCount > pCapacity)
	{
		SetCount(pCapacity);
	}

	mLayers.resize(pCapacity);
}

void FR::LayerVec::SetMinCount(int pMinCount)
{
	if (mCount < pMinCount)
	{
		SetCount(pMinCount);
	}
}

void FR::LayerVec::SetCount(int pCount)
{
	auto count = mCount;

	if (pCount == count)
	{
		return;
	}

CheckAgain:

	if (pCount > count)
	{
		Add();
		count++;
		goto CheckAgain;
	}
	else
	{
		for (int i = mCapacity - 1; i >= mCount; i--)
		{
			if (auto& layer = mLayers[i])
			{
				delete layer; layer = nullptr;
			}
		}
	}
}

FR::AnimancerLayer* FR::LayerVec::Add()
{
	auto index = mCount;

	if (index >= mLayers.size())
	{
		SetCapacity(mCapacity * 2);
	}

	mCount = index + 1;

	auto layer = new AnimancerLayer(root, index);
	mLayers[index] = layer;
	return layer;
}

FR::AnimancerLayer* FR::LayerVec::operator[](int pIndex)
{
	SetMinCount(pIndex + 1);
	return mLayers[pIndex];
}

FR::LayerVec::~LayerVec()
{
	for (auto& layer : mLayers)
	{
		if (layer)
		{
            delete layer; layer = nullptr;
		}
	}
	mLayers.clear();
}
