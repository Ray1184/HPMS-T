#pragma once

#include "engine/Tile.h"
#include "ecs/component/Graphics.h"

#include <vector>
#include <unordered_map>

namespace hpms
{
    typedef std::unordered_map<Transform2D, std::vector<Tile>> TileChunks;

    struct TileMap : public Graphics
    {
        TileChunks chunks;

        ComponentType Type() const override
        {
            return COMPONENT_TILEMAP;
        }
    };
}
