#pragma once

#include "base/Resource.h"
#include "engine/resource/ResourceSupplier.h"

#include <string>
#include <unordered_map>

namespace hpms
{

    class ResourcesHandler
    {
    private:
        static std::unordered_map<std::string, std::unordered_map<std::string, Resource*>> resourcesCache;

    public:
        static void PreloadResources(const std::string& pakId, ResourceSupplier* supplier);
        static void UnloadResources(const std::string& pakId, ResourceSupplier* supplier);
        template <typename T>
        static inline T* Provide(const std::string& pakId, const std::string& resourceName)
        {
            if (!resourcesCache.contains(pakId))
            {
                LOG_ERROR("Pack with id {} not loaded", pakId);
                RUNTIME_EXCEPTION("Pack with id {} not loaded", pakId);
            }
            if (!resourcesCache[pakId].contains(resourceName))
            {
                LOG_ERROR("Resource with name {} not present in pack {}", resourceName, pakId);
                RUNTIME_EXCEPTION("Resource with name {} not present in pack {}", resourceName, pakId);
            }
            return dynamic_cast<T*>(resourcesCache[pakId][resourceName]);
        }
    };



}