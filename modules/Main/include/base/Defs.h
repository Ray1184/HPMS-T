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
    };

    struct Transform3D
    {
        Transform2D transform2D;
        float z{0};

        inline bool operator==(const Transform3D& rhs) const
        {
            return transform2D == rhs.transform2D &&
                   z == rhs.z;
        }

        inline bool operator!=(const Transform3D& rhs) const
        {
            return !(rhs == *this);
        }

        inline bool operator<(const Transform3D& rhs) const
        {
            if (z == rhs.z)
            {
                return transform2D.y < rhs.transform2D.y;
            }
            return z < rhs.z;
        }

        inline bool operator>(const Transform3D& rhs) const
        {
            return rhs < *this;
        }

        inline bool operator<=(const Transform3D& rhs) const
        {
            return !(rhs < *this);
        }

        inline bool operator>=(const Transform3D& rhs) const
        {
            return !(*this < rhs);
        }
    };
}