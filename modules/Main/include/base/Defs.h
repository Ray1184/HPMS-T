#pragma once

#include <utility>

#define DATA_PATH "data"
#define PACKS_PATH DATA_PATH "/packs"

namespace hpms
{
    struct Transform2D
    {
        float x{0};
        float y{0};

        inline bool operator==(const Transform2D& rhs) const
        {
            return x == rhs.x &&
                   y == rhs.y;
        }

        inline bool operator!=(const Transform2D& rhs) const
        {
            return !(rhs == *this);
        }

        inline bool operator<(const Transform2D& rhs) const
        {
            return y < rhs.y;
        }

        inline bool operator>(const Transform2D& rhs) const
        {
            return rhs < *this;
        }

        inline bool operator<=(const Transform2D& rhs) const
        {
            return !(rhs < *this);
        }

        inline bool operator>=(const Transform2D& rhs) const
        {
            return !(*this < rhs);
        }
    };

}