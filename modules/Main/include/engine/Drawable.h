#pragma once

#include "base/Defs.h"
#include "engine/resource/Texture.h"

#include <vector>

namespace hpms
{
    enum RenderType
    {
        DRAWABLE_PICTURE,
        DRAWABLE_SIMPLE_SPRITE,
        DRAWABLE_TILES_POOL
    };

    enum RenderStrategy
    {
        STRATEGY_STATIC = 1,
        STRATEGY_UPDATE_VERTICES = 2
    };

    struct Drawable
    {
        std::string id;
        unsigned int layer;
        Texture* texture;
        bool updateVertices{false};
        bool forceAll{true};

        virtual ~Drawable() = default;

        [[nodiscard]] virtual RenderType GetType() const = 0;
    };
}
