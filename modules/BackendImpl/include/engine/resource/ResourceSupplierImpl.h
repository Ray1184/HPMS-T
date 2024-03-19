#pragma once

#include "base/Utils.h"
#include "engine/resource/ResourceSupplier.h"
#include "engine/resource/ResourcesImpl.h"

namespace hpms
{
    class ResourceSupplierImpl : public hpms::ResourceSupplier
    {
    public:
        inline hpms::Resource* Create(hpms::ResourceType resType) override
        {
            switch (resType)
            {
                case hpms::ResourceType::TEXTURES:
                    return SAFE_NEW(hpms::TextureImpl);
                default:
                    return nullptr;
            }

        }

        inline void Delete(hpms::ResourceType resType, hpms::Resource* resource) override
        {
            switch (resType)
            {
                case hpms::ResourceType::TEXTURES:
                    auto* ptr = dynamic_cast<TextureImpl*>(resource);
                    SAFE_DELETE(hpms::TextureImpl, ptr);
                    return;
            }
        }
    };
}