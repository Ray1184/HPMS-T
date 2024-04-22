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

        virtual std::string ResourceId() = 0;

        void Load(void* ptr, unsigned int size)
        {
            if (!loaded)
            {
                Allocate(ptr, size);
                loaded = true;
            }
        }

        void Unload()
        {
            if (loaded)
            {
                Deallocate();
                loaded = false;
            }
        }

        static ResourceType ByResourceName(const std::string& name)
        {
            static const std::unordered_map<std::string, ResourceType> resourceTypeMapping = {
                    {".png",   TEXTURES},
                    {".hpmap", MAPS},
                    {".rdef",  RES_DEFINITION},
                    {".mp3",   SOUNDS},
                    {".lua",   SCRIPTS}
            };

            const std::string extension = Strings::GetFilenameExtension(name);
            return resourceTypeMapping.at(extension);
        }
    };

};