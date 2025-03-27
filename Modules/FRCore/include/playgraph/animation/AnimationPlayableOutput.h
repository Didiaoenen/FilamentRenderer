#pragma once

#include "APlayableOutput.h"

#include <string>

namespace FR
{
	class FRCompAnimator;

	class PlayableGraph;
	class AnimationPlayable;

	class AnimationPlayableOutput
		: public APlayableOutput
	{
	public:
		AnimationPlayableOutput(PlayableGraph* pGraph, const std::string& pName, FRCompAnimator* pAnimator);

		void SetSourcePlayable(AnimationPlayable* pPlayable);

		virtual void Update(float pDeltaTime) override;

		void SetTarget(FRCompAnimator* pAnimator);

		FRCompAnimator* GetTarget() const;

	private:
		FRCompAnimator* mAnimator;

	};
}
