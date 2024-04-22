#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <bitset>

namespace hpms
{
    struct TilesChunkData : public Drawable
    {
        std::vector<Tile> tiles;

        TilesChunkData() = default;

        TilesChunkData(const std::string& id, const unsigned int layer, Texture* texture, const std::vector<Tile>& tiles, const bool updateVertices = false) : Drawable(id, layer, texture, updateVertices),
                                                                                                                                                         tiles(tiles)
        {
        }

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_TILES_CHUNK_DATA;
        }
    };
}
