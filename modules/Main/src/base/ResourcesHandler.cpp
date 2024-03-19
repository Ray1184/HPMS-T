#include "base/ResourcesHandler.h"
#include "base/PacksHandler.h"

std::unordered_map<std::string, std::unordered_map<std::string, hpms::Resource*>> hpms::ResourcesHandler::resourcesCache = std::unordered_map<std::string, std::unordered_map<std::string, hpms::Resource*>>();


void hpms::ResourcesHandler::PreloadResources(const std::string& pakId, ResourceSupplier* supplier)
{

    resourcesCache.insert({pakId, std::unordered_map<std::string, hpms::Resource*>()});
    auto process = [&](void* buffer, unsigned int size, const std::string& name)
    {
        LOG_DEBUG("Loading {} resource", name);
        hpms::ResourceType type = hpms::Resource::ByResourceName(name);
        hpms::Resource* res = supplier->Create(type);
        res->Load(buffer, size);
        resourcesCache[pakId].insert({name, res});

    };
    hpms::PacksHandler::ProcessPack(pakId, process);
    LOG_DEBUG("Pack {} resources loaded into cache", pakId);
    LOG_DEBUG("Loaded {} items from {}", resourcesCache[pakId].size(), pakId);
}

void hpms::ResourcesHandler::UnloadResources(const std::string& pakId, ResourceSupplier* supplier)
{
    LOG_DEBUG("Unloading {} items of {}", resourcesCache[pakId].size(), pakId);
    for (auto& resEntry : resourcesCache[pakId])
    {
        LOG_DEBUG("Unloading {} resource", resEntry.first);
        resEntry.second->Unload();
        hpms::ResourceType type = hpms::Resource::ByResourceName(resEntry.first);
        supplier->Delete(type, resEntry.second);
    }
    resourcesCache.erase(pakId);

}


