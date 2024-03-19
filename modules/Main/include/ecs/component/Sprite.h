#pragma once

#include "base/Defs.h"
#include "engine/Tile.h"
#include "ecs/component/Graphics.h"

#include <vector>

namespace hpms
{
    struct Sprite : public hpms::Graphics
    {
        std::vector<hpms::Tile> tiles;

        inline const ComponentType Type() const override
        {
            return COMPONENT_GRAPHICS;
        }
    };
}