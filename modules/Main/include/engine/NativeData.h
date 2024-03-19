#pragma once

namespace hpms
{
    template<typename T>
    class NativeData
    {
    public:
        virtual T* GetNative() = 0;
    };
}