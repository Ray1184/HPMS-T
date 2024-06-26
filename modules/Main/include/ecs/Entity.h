#pragma once

#include "ecs/Component.h"

#include <unordered_map>
#include <functional>
#include <string>
#include <utility>

namespace hpms
{
    typedef const std::function<void(ComponentType, Component*)> EntityComponentsVisitor;

    class Entity
    {
    private:
        std::unordered_map<ComponentType, Component*> components;
        std::string uniqueId;

    public:
        explicit Entity(std::string unique_id)
            : uniqueId(std::move(unique_id))
        {
        }

        void AddComponent(Component* component)
        {
            components[component->Type()] = component;
        }

        [[nodiscard]] bool HasComponent(const ComponentType type) const
        {
            return components.contains(type);
        }

        template<typename T>
        T* GetComponent(const ComponentType type)
        {
            if (components.contains(type))
            {
                return dynamic_cast<T*>(components[type]);
            }
            return nullptr;
        }

        void ForeachComponent(const EntityComponentsVisitor& visitor) const
        {
            for (const auto& [fst, snd]: components)
            {
                visitor(fst, snd);
            }
        }

        [[nodiscard]] std::string GetId() const
        {
            return "Entity/" + uniqueId;
        }
    };
}
