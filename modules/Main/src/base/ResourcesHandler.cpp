#include "base/ResourcesHandler.h"
#include "base/PacksHandler.h"

std::unordered_map<std::string, std::unordered_map<std::string, hpms::Resource*>> hpms::ResourcesHandler::resourcesCache = std::unordered_map<std::string, std::unordered_map<std::string, Resource*>>();


void hpms::ResourcesHandler::PreloadResources(const std::string& pakId, ResourceSupplier* supplier)
{

    resourcesCache.insert({pakId, std::unordered_map<std::string, Resource*>()});
    auto process = [&](void* buffer, const unsigned int size, const std::string& name)
    {
        LOG_DEBUG("Loading {} resource", name);
        const ResourceType type = Resource::ByResourceName(name);
        Resource* res = supplier->Create(type, name);
        res->Load(buffer, size);
        resourcesCache[pakId].insert({name, res});

    };
    PacksHandler::ProcessPack(pakId, process);
    LOG_DEBUG("Pack {} resources loaded into cache", pakId);
    LOG_DEBUG("Loaded {} items from {}", resourcesCache[pakId].size(), pakId);
}

void hpms::ResourcesHandler::UnloadResources(const std::string& pakId, ResourceSupplier* supplier)
{
    LOG_DEBUG("Unloading {} items of {}", resourcesCache[pakId].size(), pakId);
    for (auto& [fst, snd] : resourcesCache[pakId])
    {
        LOG_DEBUG("Unloading {} resource", fst);
        snd->Unload();
        const ResourceType type = Resource::ByResourceName(fst);
        supplier->Delete(type, snd);
    }
    resourcesCache.erase(pakId);

}


