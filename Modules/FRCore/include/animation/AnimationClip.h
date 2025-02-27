#pragma once

#include "Core.FRAsset.h"

#include <ozz/base/io/archive.h>
#include <ozz/animation/runtime/animation.h>

#include <string>
#include <typeinfo>

namespace FR
{
    class AnimationClip
        : public FRAsset
    {
    public:
        AnimationClip(ozz::animation::Animation&& pAnimation);

        float GetDurtion();

        const std::string& GetName();

        ozz::animation::Animation& NativePtr();

    public:
        ~AnimationClip();
    
    private:
		ozz::animation::Animation mAnimation;

    };
}