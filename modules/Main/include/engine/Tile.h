#pragma once

#include "base/Utils.h"

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 32
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
        float depth{0};

        inline bool operator==(const Tile& rhs) const
        {
            return position == rhs.position;
        }

        inline bool operator!=(const Tile& rhs) const
        {
            return !(rhs == *this);
        }

        inline bool operator<(const Tile& rhs) const
        {
           return depth < rhs.depth;
        }

        inline bool operator>(const Tile& rhs) const
        {
            return rhs < *this;
        }

        inline bool operator<=(const Tile& rhs) const
        {
            return !(rhs < *this);
        }

        inline bool operator>=(const Tile& rhs) const
        {
            return !(*this < rhs);
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
            std::size_t h1 = std::hash<float>{}(obj.position.x);
            std::size_t h2 = std::hash<float>{}(obj.position.y);
            std::size_t h3 = std::hash<float>{}(obj.depth);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}


