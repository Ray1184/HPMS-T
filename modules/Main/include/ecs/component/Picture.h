#pragma once

#include "base/Defs.h"
#include "ecs/Component.h"

#include <string>

namespace hpms
{

    struct Picture : public hpms::Component
    {
        std::string textureName;
        std::string pakId;
        unsigned int layer;

        inline const ComponentType Type() const override
        {
            return COMPONENT_PICTURE;
        }
    };
}