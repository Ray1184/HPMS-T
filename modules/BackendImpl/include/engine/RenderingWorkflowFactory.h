#pragma once

#include "engine/RenderingWorkflow.h"
#include "engine/workflow/PictureRenderingWorkflow.h"
#include "engine/workflow/TilesPoolRenderingWorkflow.h"

namespace hpms
{
    class RenderingWorkflowFactory
    {
    public:
        static RenderingWorkflow* GetRenderingWorkflow(RenderType type)
        {
            static PictureRenderingWorkflow prw;
            static TilesPoolRenderingWorkflow trw;
            switch (type)
            {
            case DRAWABLE_PICTURE:
                return &prw;
            case DRAWABLE_TILES_POOL:
                return &trw;
            default:
                LOG_ERROR("Rendering workflow not implemented");
                RUNTIME_EXCEPTION("Rendering workflow not implemented");
            }
        }
    };
}