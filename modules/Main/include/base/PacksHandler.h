#pragma once

#include <unordered_map>
#include <functional>
#include <string>

namespace hpms
{

    typedef const std::function<void(void* buffer, unsigned int, const std::string&)> ArchiveProcessorCallback;

    class PacksHandler
    {
    public:
        static void ProcessPack(const std::string& pakId, ArchiveProcessorCallback& callback);

    };
}