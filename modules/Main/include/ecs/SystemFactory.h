#pragma once

#include "ecs/System.h"
#include "ecs/system/Systems.h"

namespace hpms
{
    class SystemFactory
    {
    public:
        template<typename T>
        static System<T>* GetSystem(const SystemType type)
        {
            static RenderSystem renderSystem;
            switch (type)
            {
            case SYSTEM_RENDERER:
                return &renderSystem;
            default:
                LOG_ERROR("System not implemented");
                RUNTIME_EXCEPTION("System not implemented");
            }
        }
    };
}