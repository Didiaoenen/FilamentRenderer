#include "AnimancerPlayable.StateMap.h"

#include "AnimancerState.h"
#include "AnimancerLayer.h"
#include "AnimancerPlayable.h"

FR::StateMap::StateMap(AnimancerPlayable* pRoot)
{
	root = pRoot;
}

FR::AnimancerState* FR::StateMap::Create(AnimationClip* pClip)
{
	return Create(root->GetKey(pClip), pClip);
}

FR::AnimancerState* FR::StateMap::Create(std::any pKey, AnimationClip* pClip)
{
	auto state = new AnimancerState(pClip);
	state->SetRoot(root);
	state->SetKey(pKey);
	Register(state);
	return state;
}

FR::AnimancerState* FR::StateMap::GetOrCreate(AnimationClip* pClip, bool pAllowSetClip)
{
	return GetOrCreate(root->GetKey(pClip), pClip, pAllowSetClip);
}

FR::AnimancerState* FR::StateMap::GetOrCreate(std::any pKey, AnimationClip* pClip, bool pAllowSetClip)
{
	AnimancerState* state;
	if (TryGet(pKey, state))
	{
		if (state->Clip() != pClip)
		{
			if (pAllowSetClip)
			{
				state->SetClip(pClip);
			}
		}
	}
	else
	{
		state = Create(pKey, pClip);
	}

	return state;
}

FR::AnimancerState* FR::StateMap::Current()
{
	return root->layers[0]->CurrentState();
}

void FR::StateMap::Register(AnimancerState* pState)
{
	if (auto key = pState->Key(); key.has_value())
	{
		mStates.emplace(key, pState);
	}
}

void FR::StateMap::Unregister(AnimancerState* pState)
{
	if (auto key = pState->Key(); key.has_value())
	{
		mStates.erase(key);
	}
}

bool FR::StateMap::TryGet(std::any pKey, AnimancerState*& pState)
{
	if (!pKey.has_value())
	{
		pState = nullptr;
		return false;
	}

	if (auto find = mStates.find(pKey); find != mStates.end())
	{
		pState = find->second;
		return true;
	}

	return false;
}

FR::AnimancerState* FR::StateMap::operator[](AnimationClip* pClip)
{
	return mStates[root->GetKey(pClip)];
}

FR::StateMap::~StateMap()
{
	for (auto& [_, state] : mStates)
	{
		delete state; state = nullptr;
	}
	mStates.clear();
}
