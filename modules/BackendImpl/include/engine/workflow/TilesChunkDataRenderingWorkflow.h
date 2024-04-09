#pragma once

#include "engine/RenderingWorkflow.h"
#include "engine/renderable/TilesChunkData.h"

namespace hpms
{
    class TilesChunkDataRenderingWorkflow : public RenderingWorkflow
    {
    public:
        virtual void Render(Window* window, Drawable* item) override;

    };
}