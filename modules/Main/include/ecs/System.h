#pragma once

#include "ecs/Entity.h"

#include <vector>

namespace hpms
{

    enum SystemType
    {
        SYSTEM_RENDERER
    };

    template <typename T>
    class System
    {
    public:
        virtual void Init(std::vector<Entity*>& entities, T* args) = 0;
        virtual void Update(std::vector<Entity*>& entities, T* args) = 0;
        virtual void Cleanup(std::vector<Entity*>& entities, T* args) = 0;
    };
}