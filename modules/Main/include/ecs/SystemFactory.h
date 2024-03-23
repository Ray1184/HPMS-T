#pragma once

#include "ecs/System.h"
#include "ecs/system/Systems.h"

namespace hpms
{
    class SystemFactory
    {
    public:
        template<typename T>
        inline static hpms::System<T>* GetSystem(hpms::SystemType type)
        {
            static RenderSystem renderSystem;
            switch (type)
            {
            case hpms::SystemType::SYSTEM_RENDERER:
                return &renderSystem;
            default:
                LOG_ERROR("System not implemented");
                RUNTIME_EXCEPTION("System not implemented");
            }
        }
    };
}