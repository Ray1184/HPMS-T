#pragma once

#include "engine/RenderingWorkflow.h"
#include "engine/renderable/TilesPool.h"

namespace hpms
{
    class TilesPoolRenderingWorkflow : public hpms::RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, FrameBuffer* framebuffer, Drawable* item) override;

    };
}