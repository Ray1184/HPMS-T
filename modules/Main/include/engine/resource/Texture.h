#pragma once

#include "base/Resource.h"


namespace hpms
{

    class Texture : public hpms::Resource
    {
    public:
        virtual unsigned int Width() = 0;
        virtual unsigned int Height() = 0;
        virtual void Swap(Texture* other) = 0;

    protected:
        inline std::string Name() override
        {
            return "Texture";
        }
    };
}