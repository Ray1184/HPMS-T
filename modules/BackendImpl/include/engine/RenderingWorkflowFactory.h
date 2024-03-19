#pragma once

#include "engine/RenderingWorkflow.h"
#include "engine/workflow/PictureRenderingWorkflow.h"
#include "engine/workflow/TilesPoolRenderingWorkflow.h"

namespace hpms
{
    class RenderingWorkflowFactory
    {
    public:
        inline static hpms::RenderingWorkflow* GetRenderingWorkflow(hpms::RenderType type)
        {
            static hpms::PictureRenderingWorkflow prw;
            static hpms::TilesPoolRenderingWorkflow trw;
            switch (type)
            {
                case RenderType::DRAWABLE_PICTURE:
                    return &prw;
                case RenderType::DRAWABLE_TILES_POOL:
                    return &trw;
                default:
                    LOG_ERROR("Rendering workflow not implemented");
                    RUNTIME_EXCEPTION("Rendering workflow not implemented");
            }
        }
    };
}