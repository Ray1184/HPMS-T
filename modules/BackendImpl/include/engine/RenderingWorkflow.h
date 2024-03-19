#pragma once

#include "engine/Renderer.h"
#include "engine/Window.h"
#include "engine/FrameBuffer.h"
#include "engine/resource/Texture.h"

namespace hpms
{
    class RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, FrameBuffer* framebuffer, Drawable* item) = 0;
    };
}