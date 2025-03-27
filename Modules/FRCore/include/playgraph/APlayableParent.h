#pragma once

#include <ozz/base/containers/vector.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/animation/runtime/blending_job.h>

#include <vector>
#include <cstdint>

namespace FR
{
    class APlayable;

    class APlayableParent
	{
	public:
		APlayableParent() = default;

		virtual void RemovePlayable(uint32_t pIndex) = 0;

		virtual void AddPlayable(APlayable* pPlayable, uint32_t pIndex) = 0;

		virtual void SetInputWeight(uint32_t pIndex, float pWeight) = 0;

		virtual void SetInputCount(uint32_t pCount) = 0;

		const ozz::vector<APlayable*>& GetPlayables() const
		{
			return mPlayables;
		}

	public:
		virtual ~APlayableParent() = default;

	protected:
		ozz::vector<APlayable*> mPlayables;

	};
}