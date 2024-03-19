#pragma once

#include "base/Defs.h"
#include "ecs/component/Graphics.h"

#include <string>

namespace hpms
{

    struct Picture : public hpms::Graphics
    {
        inline const ComponentType Type() const override
        {
            return COMPONENT_GRAPHICS;
        }
    };
}