#pragma once

#include "engine/Renderer.h"
#include "engine/Window.h"

namespace hpms
{
    class RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, Drawable* item) = 0;
    };
}