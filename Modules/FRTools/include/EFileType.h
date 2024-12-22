#pragma once

#include <cstdint>

namespace FR
{
    enum class EFileType : uint8_t
    {
        NONE,
        SCENE,
        MODEL,
        SHADER,
        TEXTURE,
        MATERIAL,
        ANIMATION,
        OZZMODEL,
        FONT,
    };
}