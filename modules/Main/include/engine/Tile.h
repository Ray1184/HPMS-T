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
        Transform2D position{0, 0};
        Transform2D texCoords{0, 0};
    };
}
