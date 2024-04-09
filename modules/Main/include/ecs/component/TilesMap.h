#pragma once

#include "engine/renderable/TilesChunkData.h"
#include "ecs/component/Graphics.h"

#include <vector>
#include <unordered_map>

namespace hpms
{
    struct TilesMap : public Graphics
    {
        std::unordered_map<Transform2D, TilesChunkData> chunks;

        ComponentType Type() const override
        {
            return COMPONENT_TILES_MAP;
        }
    };
}
