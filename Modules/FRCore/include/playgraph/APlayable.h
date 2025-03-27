#pragma once

#include <Core.FRObject.h>

namespace FR
{
	class PlayableGraph;
	class APlayableOutput;

	class APlayable
		: public FRObject
	{
	public:
		APlayable() = default;

		virtual bool Update(float pDeltaTime) = 0;

		virtual bool Sample() = 0;

		virtual void Pause() {}

		virtual void Play() {}

	public:
		virtual ~APlayable() = default;

	protected:
		PlayableGraph* mGraph{ nullptr };

		APlayableOutput* mOutput{ nullptr };

	};
}
