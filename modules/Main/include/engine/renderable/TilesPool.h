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

        TilesPool(unsigned int layer, Texture* texture, const std::string& id, const int flags = STRATEGY_STATIC);

        void AddTile(const Tile& tile);

        std::vector<Tile>* GetTiles();

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_TILES_POOL;
        }
    };
}