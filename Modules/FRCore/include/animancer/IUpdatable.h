#pragma once

namespace FR
{
	class IUpdatable
    {
    public:
        virtual void Update() = 0;
    
    public:
        virtual ~IUpdatable() = default;

    };
}