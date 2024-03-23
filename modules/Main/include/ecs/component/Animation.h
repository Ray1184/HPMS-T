#pragma once

#include "base/Defs.h"
#include "engine/Tile.h"
#include "ecs/Component.h"

#include <vector>
#include <unordered_map>

namespace hpms
{

    struct Animation : public hpms::Component
    {
        std::string name;
        unsigned int frameCount{1};
        unsigned int currentFrame{0};
        float tpf{1};
        std::vector<hpms::Tile> tiles;

        ComponentType Type() const override
        {
            return COMPONENT_ANIMATION;
        }
    };
}