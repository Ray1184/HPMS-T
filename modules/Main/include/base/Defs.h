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

        bool operator==(const Transform2D& rhs) const
        {
            return x == rhs.x &&
                   y == rhs.y;
        }

        bool operator!=(const Transform2D& rhs) const
        {
            return !(rhs == *this);
        }

        bool operator<(const Transform2D& rhs) const
        {
            return y < rhs.y;
        }

        bool operator>(const Transform2D& rhs) const
        {
            return rhs < *this;
        }

        bool operator<=(const Transform2D& rhs) const
        {
            return !(rhs < *this);
        }

        bool operator>=(const Transform2D& rhs) const
        {
            return !(*this < rhs);
        }
    };
}
namespace std
{
    template<>
    struct hash<hpms::Transform2D>
    {
        std::size_t operator()(const hpms::Transform2D& obj) const
        {
            std::size_t h1 = std::hash<float>{}(obj.x);
            std::size_t h2 = std::hash<float>{}(obj.y);
            return h1 ^ (h2 << 1);
        }
    };
}