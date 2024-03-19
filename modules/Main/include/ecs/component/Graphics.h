#pragma once

#include "base/Defs.h"
#include "ecs/Component.h"

#include <string>

namespace hpms
{

    struct Graphics : public hpms::Component
    {
        std::string textureName;
        std::string pakId;
        bool visible{true};
        unsigned int layer;
    };
}