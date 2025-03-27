#include "PlayableGraphManager.h"

#include "PlayableGraph.h"

FR::PlayableGraphManager* FR::PlayableGraphManager::Instance()
{
    if (!sInstance)
    {
        sInstance = new PlayableGraphManager();
    }

	return sInstance;
}

void FR::PlayableGraphManager::AddGraph(PlayableGraph* pGraph)
{
    mGraphs.emplace_back(pGraph);
}

void FR::PlayableGraphManager::Update(float pDeltaTime)
{
    for (const auto& graph : mGraphs)
    {
        graph->Update(pDeltaTime);
    }
}
