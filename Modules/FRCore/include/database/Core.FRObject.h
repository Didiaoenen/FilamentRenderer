#pragma once

#include <string>
#include <cstdint>

namespace FR
{
    class FRObject
    {
    public:
        FRObject();

    public:
        virtual ~FRObject() = default;

    protected:
        uint64_t GenUUID();

    public:
		uint64_t uUID;

        std::string name;

    };
}