#pragma once

#include "base/Defs.h"
#include "engine/Tile.h"
#include "ecs/Component.h"

#include <vector>

namespace hpms
{
    struct Sprite : public hpms::Component
    {
        std::string textureName;
        std::string pakId;
        bool visible{true};
        std::vector<hpms::Tile> tiles;
        unsigned int layer;

        inline const ComponentType Type() const override
        {
            return COMPONENT_SPRITE;
        }
    };
}