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
        virtual void Render(hpms::Window* window, hpms::FrameBuffer* framebuffer, std::vector<hpms::Drawable*>* drawables) = 0;
    };
}