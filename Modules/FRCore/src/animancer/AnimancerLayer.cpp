#include "AnimancerLayer.h"

#include "AnimancerState.h"
#include "AnimancerPlayable.h"

#include "PlayableGraph.h"
#include "AnimationMixerPlayable.h"

#include <glm/ext.hpp>

FR::AnimancerLayer::AnimancerLayer(AnimancerPlayable* pRoot, int pIndex)
{
	mRoot = pRoot;
	mIndex = pIndex;
	CreatePlayable();
}

void FR::AnimancerLayer::CreatePlayable(AnimationPlayable*& pPlayable)
{
	pPlayable = new AnimationMixerPlayable(Root()->Graph(), 2);
}

FR::AnimancerLayer* FR::AnimancerLayer::Layer()
{
	return this;
}

FR::IPlayableWarp* FR::AnimancerLayer::Parent()
{
	return mRoot;
}

FR::AnimancerState* FR::AnimancerLayer::CurrentState()
{
	return mCurrState;
}

void FR::AnimancerLayer::SetCurrentState(AnimancerState* pState)
{
	mCurrState = pState;
}

void FR::AnimancerLayer::AddChild(AnimancerState* pState)
{
	if (pState->Parent() == this)
	{
		return;
	}

	if (auto parent = dynamic_cast<APlayableParent*>(mPlayable))
	{
		parent->SetInputCount(mStates.size() + 1);
	}

	pState->SetRoot(mRoot);
	pState->SetParent(this, mStates.size());
}

void FR::AnimancerLayer::OnAddChild(AnimancerState* pState)
{
	OnAddChild(mStates, pState);
}

void FR::AnimancerLayer::OnRemoveChild(AnimancerState* pState)
{
	if (auto parentPlayable = dynamic_cast<APlayableParent*>(mPlayable))
	{
		Root()->Graph()->Disconnect(parentPlayable, pState->Index());

		mStates.erase(std::remove(mStates.begin(), mStates.end(), pState), mStates.end());

		parentPlayable->SetInputCount(mStates.size());
	}
}

FR::AnimancerState* FR::AnimancerLayer::CreateState(AnimationClip* pClip)
{
	return CreateState(mRoot->GetKey(pClip), pClip);
}

FR::AnimancerState* FR::AnimancerLayer::CreateState(std::any pKey, AnimationClip* pClip)
{
	auto state = new AnimancerState();
	state->SetKey(pKey);
	AddChild(state);
	return state;
}

FR::AnimancerState* FR::AnimancerLayer::GetState(std::any& pKey)
{
	auto& tKey = pKey;
	while (tKey.type() == typeid(AnimancerState*))
	{
        auto keyState = std::any_cast<AnimancerState*>(tKey);
		if (keyState->Parent() == this)
		{
			pKey = keyState->Key();
			return keyState;
		}
		else if (!keyState->Parent())
		{
			pKey = keyState->Key();
			AddChild(keyState);
			return keyState;
		}
		else
		{
			tKey = keyState->Key();
		}
	}

	while (true)
	{
		AnimancerState* state;
		if (!mRoot->states.TryGet(pKey, state))
		{
			return nullptr;
		}

		if (state->Parent() == this)
		{
			return state;
		}
		else if (!state->Parent())
		{
			AddChild(state);
			return state;
		}
		else
		{
			pKey = state;
		}
	}
}

FR::AnimancerState* FR::AnimancerLayer::GetOrCreateState(AnimancerState* pState)
{
	if (pState->Parent() == this)
	{
		return pState;
	}

	if (!pState->Parent())
	{
		AddChild(pState);
		return pState;
	}

	auto key = pState->Key();
	if (!key.has_value())
	{
		key = pState;
	}

	auto state = GetState(key);

	if (!state)
	{
		state = pState->Clone(mRoot);
		state->SetKey(key);
		AddChild(state);
	}

	return state;
}

FR::AnimancerState* FR::AnimancerLayer::GetOrCreateState(AnimationClip* pClip, bool pAllowSetClip)
{
	return GetOrCreateState(mRoot->GetKey(pClip), pClip, pAllowSetClip);
}

FR::AnimancerState* FR::AnimancerLayer::GetOrCreateState(std::any pKey, AnimationClip* pClip, bool pAllowSetClip)
{
	auto state = GetState(pKey);

	if (!state)
	{
		return CreateState(pKey, pClip);
	}

	if (state->Clip() != pClip)
	{
		if (pAllowSetClip)
		{
			state->SetClip(pClip);
		}
	}

	return state;
}

FR::AnimancerState* FR::AnimancerLayer::Play(AnimationClip* pClip)
{
	return Play(GetOrCreateState(pClip));
}

FR::AnimancerState* FR::AnimancerLayer::Play(AnimancerState* pState)
{
	if (Weight() == 0.f && targetWeight == 0.f)
	{
		SetWeight(1.f);
	}

	auto state = GetOrCreateState(pState);

	mCurrState = state;

	state->Play();

	for (int i = mStates.size() - 1; i >= 0; i--)
	{
		auto otherState = mStates[i];
		if (otherState != state)
		{
			otherState->Stop();
		}
	}

    return state;
}

FR::AnimancerState* FR::AnimancerLayer::Play(AnimationClip* pClip, float pFadeDuration)
{
	return Play(GetOrCreateState(pClip), pFadeDuration);
}

FR::AnimancerState* FR::AnimancerLayer::Play(AnimancerState* pState, float pFadeDuration)
{
	if (pFadeDuration <= 0 || (Index() == 0 && Weight() == 0))
	{
		SetWeight(1.f);
		pState = Play(pState);
		return pState;
	}

	StartFade(1.f, pFadeDuration);
	if (Weight() == 0)
	{
		return Play(pState);
	}

	pState = GetOrCreateState(pState);

	mCurrState = pState;

	if (pState->IsPlaying() && pState->targetWeight == 1.f &&
		(pState->Weight() == 1.f || pState->fadeSpeed * pFadeDuration > glm::abs(1.f - pState->Weight())))
	{
		OnStartFade();
	}
	else
	{
		pState->SetPlaying(true);
		pState->StartFade(1.f, pFadeDuration);

		for (int i = mStates.size() - 1; i >= 0; i--)
		{
			auto otherState = mStates[i];
			if (otherState != pState)
			{
				otherState->StartFade(0, pFadeDuration);
			}
		}
	}

	return pState;
}

void FR::AnimancerLayer::OnStartFade()
{
	for (int i = mStates.size() - 1; i >= 0; i--)
	{
		mStates[i]->OnStartFade();
	}
}

FR::AnimancerLayer::~AnimancerLayer()
{
}
