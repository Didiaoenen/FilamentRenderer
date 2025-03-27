#pragma once

namespace FR
{
    template<typename T>
    class ICopyable
    {
    public:
        virtual void CopyFrom(T* pCopyFrom) = 0;

    public:
        virtual ~ICopyable() = default;

    };
}