#pragma once

#include <string>

namespace hpms
{

    enum ComponentType {
        COMPONENT_GRAPHICS,
        COMPONENT_MOVABLE,
        COMPONENT_ANIMATION,
        COMPONENT_CAMERA,
        COMPONENT_AABB,
        COMPONENT_EVENT,
        COMPONENT_TEXT
    };

    class Component
    {
    public:
        virtual const ComponentType Type() const = 0;
    };
}