#pragma once

#include "engine/RenderingWorkflow.h"

namespace hpms
{
    class PictureRenderingWorkflow : public hpms::RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, FrameBuffer* framebuffer, Drawable* item) override;
    };
}