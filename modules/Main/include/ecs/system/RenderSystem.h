#pragma once

#include "ecs/Entity.h"
#include "ecs/component/Components.h"
#include "engine/Renderer.h"
#include "engine/FrameBuffer.h"
#include "engine/Window.h"

#include <vector>

namespace hpms
{
    class RenderSystem
    {
    public:
        static void Init(std::vector<Entity*>& entities, Renderer* renderer, Window* window, FrameBuffer* framebuffer);
        static void Update(std::vector<Entity*>& entities, Renderer* renderer, Window* window, FrameBuffer* framebuffer);
    };
}