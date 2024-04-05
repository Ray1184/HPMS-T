#pragma once

#include "engine/Tile.h"
#include "ecs/component/Graphics.h"

#include <vector>

namespace hpms
{
    struct TileMap : public Graphics
    {
        std::vector<Tile> tiles;

        ComponentType Type() const override
        {
            return COMPONENT_TILEMAP;
        }
    };
}