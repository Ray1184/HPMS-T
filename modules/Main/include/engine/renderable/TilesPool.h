#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <unordered_map>
#include <unordered_set>
#include <bitset>

namespace hpms
{
    class TilesPool : public Drawable
    {
    private:
        std::string id;
        std::unordered_set<Tile> tiles;

    public:

        TilesPool(unsigned int layer, Texture* texture, const std::string& id);

        void AddTile(const Tile& tile);

        std::unordered_set<Tile>* GetTiles();

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_TILES_POOL;
        }

        [[nodiscard]] const std::string GetId() const override
        {
            return "TilesPool" + id;
        }
    };
}