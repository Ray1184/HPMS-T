#pragma once

#include "base/Defs.h"
#include "ecs/Component.h"

namespace hpms
{
    struct Movable : public hpms::Component
    {
        Transform3D position{0, 0};

        inline const ComponentType Type() const override
        {
            return COMPONENT_MOVABLE;
        }
    };
}