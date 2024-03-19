#pragma once

#include "base/Utils.h"

#include <unordered_map>

namespace hpms
{
    enum ResourceType
    {
        TEXTURES,
        MAPS,
        RES_DEFINITION,
        SOUNDS,
        SCRIPTS
    };

    class Resource
    {
    private:
        bool loaded{false};
    protected:
        virtual void Allocate(void* ptr, unsigned int size) = 0;

        virtual void Deallocate() = 0;

        virtual std::string Name() = 0;

    public:

        virtual ~Resource() = default;

        inline void Load(void* ptr, unsigned int size)
        {
            if (!loaded)
            {
                Allocate(ptr, size);
                loaded = true;
            }
        }

        inline void Unload()
        {
            if (loaded)
            {
                Deallocate();
                loaded = false;
            }
        }

        inline static hpms::ResourceType ByResourceName(const std::string& name)
        {
            static const std::unordered_map<std::string, hpms::ResourceType> resourceTypeMapping = {
                    {".png",   hpms::ResourceType::TEXTURES},
                    {".hpmap", hpms::ResourceType::MAPS},
                    {".rdef",  hpms::ResourceType::RES_DEFINITION},
                    {".mp3",   hpms::ResourceType::SOUNDS},
                    {".lua",   hpms::ResourceType::SCRIPTS}
            };

            std::string extension = hpms::Strings::GetFilenameExtension(name);
            return resourceTypeMapping.at(extension);
        }
    };

};