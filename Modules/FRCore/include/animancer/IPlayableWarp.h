#pragma once

namespace FR
{
    class AnimationPlayable;

    class IPlayableWarp
    {
    public:
        virtual IPlayableWarp* Parent() = 0;

        virtual AnimationPlayable* Playable() = 0;

#pragma region Get/Set
		virtual float Weight() = 0;

		virtual void SetWeight(float pWeight) = 0;

		virtual float Speed() = 0;

		virtual void SetSpeed(float pSeed) = 0;
#pragma endregion

    public:
        virtual ~IPlayableWarp() = default;

    };
}