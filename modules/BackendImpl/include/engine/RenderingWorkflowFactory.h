#pragma once

#include "engine/RenderingWorkflow.h"
#include "engine/workflow/PictureDataRenderingWorkflow.h"
#include "engine/workflow/TilesChunkDataRenderingWorkflow.h"
#include "engine/workflow/SpriteDataRenderingWorkflow.h"

namespace hpms
{
    class RenderingWorkflowFactory
    {
    public:
        static RenderingWorkflow* GetRenderingWorkflow(RenderType type)
        {
            static PictureDataRenderingWorkflow prw;
            static TilesChunkDataRenderingWorkflow trw;
            static SpriteDataRenderingWorkflow srw;
            switch (type)
            {
                case DRAWABLE_PICTURE:
                    return &prw;
                case DRAWABLE_TILES_CHUNK_DATA:
                    return &trw;
                case DRAWABLE_SPRITE:
                    return &srw;
                default:
                    LOG_ERROR("Rendering workflow not implemented");
                    RUNTIME_EXCEPTION("Rendering workflow not implemented");
            }
        }
    };
}
