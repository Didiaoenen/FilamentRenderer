#pragma once

#include <map>
#include <vector>
#include <cstdint>

namespace FR
{
	class APlayable;
	class APlayableParent;
    class APlayableOutput;

	class PlayableGraph
	{
	public:
		PlayableGraph();

		void Update(float pDeltaTime);

		void Connect(APlayable* pSource, uint32_t pOutputPort, APlayableParent* pDestination, uint32_t pInputPort);

		void Disconnect(APlayableParent* pInput, int pInputPort);

		void AddOutput(APlayableOutput* pOutput);

		void AddPlayable(APlayable* pPlayable);

		void DestroyPlayable(APlayable* pPlayable);

		APlayableOutput* GetOutput(APlayable* pPlayable);

		void Play();

		void Stop();

	public:
		virtual ~PlayableGraph();

	public:
		std::vector<APlayable*> mPlayables;

		std::vector<APlayableOutput*> mOutputs;

	};
}