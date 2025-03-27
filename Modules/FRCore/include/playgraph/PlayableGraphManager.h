#pragma once

#include <vector>

namespace FR
{
    class PlayableGraph;

    class PlayableGraphManager
    {
    public:
        PlayableGraphManager() = default;

        static PlayableGraphManager* Instance();

        void AddGraph(PlayableGraph* pGraph);

        void Update(float pDeltaTime);

    public:
        ~PlayableGraphManager() = default;

    private:
        inline static PlayableGraphManager* sInstance{ nullptr };

        std::vector<PlayableGraph*> mGraphs;

    };
}