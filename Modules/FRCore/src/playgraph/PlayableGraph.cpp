#include "PlayableGraph.h"

#include "APlayable.h"
#include "APlayableParent.h"
#include "APlayableOutput.h"
#include "PlayableGraphManager.h"

FR::PlayableGraph::PlayableGraph()
{
	PlayableGraphManager::Instance()->AddGraph(this);
}

void FR::PlayableGraph::Update(float pDeltaTime)
{
	for (const auto& output : mOutputs)
	{
		if (auto playable = output->GetSourcePlayable())
		{
			playable->Update(pDeltaTime);
			playable->Sample();
		}

        output->Update(pDeltaTime);
	}
}

void FR::PlayableGraph::Connect(APlayable* pSource, uint32_t pOutputPort, APlayableParent* pDestination, uint32_t pInputPort)
{
	pDestination->AddPlayable(pSource, pInputPort);
}

void FR::PlayableGraph::Disconnect(APlayableParent* pInput, int pInputPort)
{
	pInput->RemovePlayable(pInputPort);
}

void FR::PlayableGraph::AddOutput(APlayableOutput* pOutput)
{
	mOutputs.emplace_back(pOutput);
}

void FR::PlayableGraph::AddPlayable(APlayable* pPlayable)
{
	mPlayables.emplace_back(pPlayable);
}

void FR::PlayableGraph::DestroyPlayable(APlayable* pPlayable)
{
}

FR::APlayableOutput* FR::PlayableGraph::GetOutput(APlayable* pPlayable)
{
	for (const auto& output : mOutputs)
	{
		if (output->GetSourcePlayable() == pPlayable)
		{
			return output;
		}
	}

	return nullptr;
}

void FR::PlayableGraph::Play()
{
}

void FR::PlayableGraph::Stop()
{
}

FR::PlayableGraph::~PlayableGraph()
{
	for (auto& playable : mPlayables)
	{
		delete playable;
	}
	mPlayables.clear();
}
