#pragma once

#include "base/Defs.h"
#include "ecs/Component.h"

namespace hpms
{
    struct Camera : public hpms::Component
    {
        Transform2D position;

        ComponentType Type() const override
        {
            return COMPONENT_CAMERA;
        }
    };
}