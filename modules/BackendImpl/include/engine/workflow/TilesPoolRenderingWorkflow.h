#pragma once

#include "engine/RenderingWorkflow.h"
#include "engine/renderable/TilesPool.h"

namespace hpms
{
    class TilesPoolRenderingWorkflow : public RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, Drawable* item) override;

    };
}