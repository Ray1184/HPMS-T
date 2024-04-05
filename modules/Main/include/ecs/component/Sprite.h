#pragma once

#include "engine/Tile.h"
#include "ecs/component/Graphics.h"

#include <vector>

namespace hpms
{
    struct Sprite : public Graphics
    {
        std::vector<Tile> tiles;
        int width;
        int height;

        ComponentType Type() const override
        {
            return COMPONENT_SPRITE;
        }
    };
}