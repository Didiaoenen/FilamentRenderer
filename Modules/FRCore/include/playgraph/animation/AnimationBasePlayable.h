#pragma once

#include "APlayableParent.h"
#include "AnimationPlayable.h"

namespace FR
{
	class AnimationBasePlayable
		: public AnimationPlayable, public APlayableParent
	{
	public:
		AnimationBasePlayable(PlayableGraph* pGraph, uint32_t pInputCount);

		virtual bool Update(float pDeltaTime) override;

		virtual bool Sample() override;

		virtual bool InitData() override;

		virtual void SetTimeRatio(float pTime) override;

		virtual void SetSpeed(float pSpeed) override;

		virtual float GetDuration() override;

		virtual void RemovePlayable(uint32_t pIndex) override;

		virtual void AddPlayable(APlayable* pPlayable, uint32_t pIndex) override;

		virtual void SetInputWeight(uint32_t pIndex, float pWeight) override;

		virtual void SetInputCount(uint32_t pInputCount) override;

	protected:
		void UpdateBlendParameters();

		bool Blend();

	public:
		virtual ~AnimationBasePlayable();

	};
}