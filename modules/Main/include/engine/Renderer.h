#pragma once

#include "engine/Drawable.h"
#include "engine/Window.h"
#include "engine/FrameBuffer.h"

#include <vector>

namespace hpms
{
    class Renderer
    {
    public:
        virtual void Render(Window* window, FrameBuffer* framebuffer, std::vector<Drawable*>* drawables) = 0;
    };
}