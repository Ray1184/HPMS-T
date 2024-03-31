#pragma once

#include "engine/RenderingWorkflow.h"

namespace hpms
{
    class PictureRenderingWorkflow : public RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, Drawable* item) override;
    };
}