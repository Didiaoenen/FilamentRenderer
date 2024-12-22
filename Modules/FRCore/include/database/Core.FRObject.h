#pragma once

#include <string>

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
        uint64_t mUUID;
        std::string name;

    };
}