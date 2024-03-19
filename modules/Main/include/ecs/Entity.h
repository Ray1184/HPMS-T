#pragma once

#include "ecs/Component.h"

#include <string>
#include <unordered_map>

namespace hpms
{

    class Entity
    {
    private:
        std::unordered_map<ComponentType, Component*> components;
        bool changed{true};

    public:
        inline void AddComponent(Component* component)
        {
            changed = true;
            components[component->Type()] = component;
        }

        inline bool HasComponent(ComponentType type)
        {
            return components.contains(type);
        }

        inline bool IsChanged() const
        {
            return changed;
        }

        inline void SetChanged(bool changed)
        {
            Entity::changed = changed;
        }

        template <typename T>
        inline T* GetComponent(ComponentType type)
        {
            if (components.contains(type))
            {
                return dynamic_cast<T*>(components[type]);
            }
            return nullptr;
        }
    };

}