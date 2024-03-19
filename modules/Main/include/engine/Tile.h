#pragma once

#include "base/Utils.h"

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 16 * 16 * 16
#endif

#ifndef TILE_SIZE
#define TILE_SIZE 16
#endif

#ifndef MAX_TILES_PER_LAYER_ON_SCREEN
#define MAX_TILES_PER_LAYER_ON_SCREEN 2048
#endif

namespace hpms
{
    struct Tile
    {
        Transform3D position;
        Transform2D texCoords;
        Transform2D screenPosition;

        inline bool operator==(const Tile& rhs) const
        {
            return position == rhs.position;
        }

        inline bool operator!=(const Tile& rhs) const
        {
            return !(rhs == *this);
        }
    };
}

namespace std
{
    template<>
    struct hash<hpms::Tile>
    {
        std::size_t operator()(const hpms::Tile& obj) const
        {
            std::size_t h1 = std::hash<float>{}(obj.position.transform2D.x);
            std::size_t h2 = std::hash<float>{}(obj.position.transform2D.y);
            std::size_t h3 = std::hash<float>{}(obj.position.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}


