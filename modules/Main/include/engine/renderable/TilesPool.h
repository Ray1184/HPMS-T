#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <unordered_map>
#include <unordered_set>
#include <bitset>

namespace hpms
{
    class TilesPool : public hpms::Drawable
    {
    private:
        std::string id;
        std::unordered_set<hpms::Tile> tiles;

    public:
        TilesPool(unsigned int layer, Texture* texture);

        void AddTile(Tile& tile);

        std::unordered_set<hpms::Tile>* GetTiles();

        [[nodiscard]] inline RenderType GetType() const override
        {
            return RenderType::DRAWABLE_TILES_POOL;
        }

        [[nodiscard]] inline const std::string GetId() const override
        {
            return "TilesPool/" + id;
        }
    };
}