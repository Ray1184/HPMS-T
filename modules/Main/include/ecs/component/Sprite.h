#pragma once

#include "base/Defs.h"
#include "engine/Tile.h"
#include "ecs/component/Graphics.h"

#include <vector>

namespace hpms
{
    struct Sprite : public hpms::Graphics
    {
        std::vector<Tile> tiles;

        ComponentType Type() const override
        {
            return COMPONENT_SPRITE;
        }
    };
}