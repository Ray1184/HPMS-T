#pragma once

namespace hpms
{

    enum ComponentType {
        COMPONENT_TILEMAP,
        COMPONENT_SPRITE,
        COMPONENT_PICTURE,
        COMPONENT_MOVABLE,
        COMPONENT_ANIMATION,
        COMPONENT_CAMERA,
        COMPONENT_AABB,
        COMPONENT_EVENT,
        COMPONENT_TEXT
    };

    struct Component
    {
        virtual ~Component() = default;

        [[nodiscard]] virtual ComponentType Type() const = 0;
    };
}