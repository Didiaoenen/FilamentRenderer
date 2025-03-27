#pragma once

namespace FR
{
    class APlayable;
	class PlayableGraph;

    class APlayableOutput
	{
	public:
        APlayableOutput() = default;

		virtual void SetSourcePlayable(APlayable* pPlayable);

		virtual void Update(float pDeltaTime) = 0;

		APlayable* GetSourcePlayable() const;

	public:
		virtual ~APlayableOutput() = default;

	protected:
		PlayableGraph* mGraph{ nullptr };

        APlayable* mSourcePlayable{ nullptr };

	};
}