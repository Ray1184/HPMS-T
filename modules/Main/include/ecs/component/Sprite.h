#pragma once

#include "engine/renderable/SpriteData.h"
#include "ecs/component/Graphics.h"

namespace hpms
{
    struct Sprite : public Graphics
    {
        Transform2D key;
        SpriteData sprite;

        ComponentType Type() const override
        {
            return COMPONENT_SPRITE;
        }
    };
}
