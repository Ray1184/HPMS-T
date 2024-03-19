#pragma once

namespace hpms
{
    class FrameBuffer
    {
    public:
        virtual unsigned int GetWidth() const = 0;

        virtual unsigned int GetHeight() const = 0;
    };
}