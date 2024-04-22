#pragma once

#include "base/Resource.h"

namespace hpms
{
    class ResourceSupplier
    {
    public:
        virtual ~ResourceSupplier() = default;

        virtual Resource* Create(ResourceType resType, const std::string& resId) = 0;
        virtual void Delete(ResourceType resType, Resource*) = 0;

    };
}