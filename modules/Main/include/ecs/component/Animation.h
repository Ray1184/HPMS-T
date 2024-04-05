#pragma once

#include "engine/Tile.h"
#include "ecs/Component.h"

#include <vector>

namespace hpms
{

    struct Animation : public Component
    {
        std::string name;
        unsigned int frameCount{1};
        unsigned int currentFrame{0};
        float tpf{1};
        std::vector<Tile> tiles;

        ComponentType Type() const override
        {
            return COMPONENT_ANIMATION;
        }
    };
}