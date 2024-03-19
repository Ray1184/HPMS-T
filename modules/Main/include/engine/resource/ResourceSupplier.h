#pragma once

#include "base/Resource.h"

namespace hpms
{
    class ResourceSupplier
    {
    public:
        virtual hpms::Resource* Create(hpms::ResourceType resType) = 0;
        virtual void Delete(hpms::ResourceType resType, hpms::Resource*) = 0;

    };
}