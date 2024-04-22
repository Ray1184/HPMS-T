#pragma once

#include "base/Utils.h"
#include "engine/resource/ResourceSupplier.h"
#include "engine/resource/ResourcesImpl.h"

namespace hpms
{
    class ResourceSupplierImpl : public ResourceSupplier
    {
    public:
        Resource* Create(ResourceType resType, const std::string& resId) override
        {
            switch (resType)
            {
            case TEXTURES:
                return SAFE_NEW(TextureImpl, resId);
            default:
                return nullptr;
            }

        }

        void Delete(ResourceType resType, Resource* resource) override
        {
            switch (resType)
            {
            case TEXTURES:
                auto* ptr = dynamic_cast<TextureImpl*>(resource);
                SAFE_DELETE(TextureImpl, ptr);
                return;
            }
        }
    };
}