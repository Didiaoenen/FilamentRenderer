#pragma once

#include "APlayableParent.h"
#include "AnimationPlayable.h"

#include <vector>

namespace FR
{
    class PlayableGraph;

	class AnimationMixerPlayable
		: public AnimationPlayable, public APlayableParent
	{
	public:

		enum class EBlendType
		{
			EQUAL,
			CROSS_DISSOLVE,
			CROSS_DISSOLVE_SYNC,
			MANUAL
		};

		AnimationMixerPlayable(PlayableGraph* pGraph, uint32_t pMixerCount);

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample() override;
		
		virtual bool InitData() override;

		virtual void SetTimeRatio(float pTimeRatio) override;

		virtual void SetSpeed(float pSpeed) override;

		virtual float GetDuration() override;

		virtual void RemovePlayable(uint32_t pIndex) override;

		virtual void AddPlayable(APlayable* pPlayable, uint32_t pIndex) override;

		virtual void SetInputWeight(uint32_t pIndex, float pWeight) override;

		virtual void SetInputCount(uint32_t pInputCount) override;

	private:
		void UpdateBlendParameters();

		bool Blend();

	public:
		~AnimationMixerPlayable() = default;

	};
}