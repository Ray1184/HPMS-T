#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <bitset>

namespace hpms
{
    struct TilesPool : public Drawable
    {
        std::vector<Tile> tiles;

        TilesPool();

        TilesPool(unsigned int layer, Texture* texture, const std::string& id, const std::vector<Tile>& tiles, const int flags = STRATEGY_STATIC);

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_TILES_POOL;
        }
    };
}
