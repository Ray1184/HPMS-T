#pragma once

#include "base/Utils.h"

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 24
#endif

#ifndef TILE_SIZE
#define TILE_SIZE 16
#endif

namespace hpms
{
    struct Tile
    {
        Tile()
        {
        }

        Tile(const Transform2D& position, const Transform2D& texCoords) : position(position), texCoords(texCoords)
        {
        }

        Transform2D position{0, 0};
        Transform2D texCoords{0, 0};
    };
}
