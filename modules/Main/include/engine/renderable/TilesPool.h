#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <bitset>

namespace hpms
{

    class TilesPool : public Drawable
    {
    private:
        std::vector<Tile> tiles;

    public:

        TilesPool(unsigned int layer, Texture* texture, const std::string& id, const std::vector<Tile>& tiles, const int flags = STRATEGY_STATIC);

        std::vector<Tile>* GetTiles();

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_TILES_POOL;
        }
    };
}