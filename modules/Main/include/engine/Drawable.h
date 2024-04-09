#pragma once

#include "engine/resource/Texture.h"

#include <unordered_map>

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
        std::unordered_map<std::string, std::string> tempData;

        virtual ~Drawable() = default;

        [[nodiscard]] virtual RenderType GetType() const = 0;
    };
}
