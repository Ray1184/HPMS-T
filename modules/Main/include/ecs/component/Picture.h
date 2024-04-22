#pragma once

#include "engine/renderable/PictureData.h"
#include "ecs/component/Graphics.h"

namespace hpms
{

    struct Picture : public hpms::Graphics
    {
        Transform2D key;
        PictureData picture;

        ComponentType Type() const override
        {
            return COMPONENT_PICTURE;
        }
    };
}