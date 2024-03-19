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
    private:
        static void Verify(Entity* entity);
    public:
        static void Update(std::vector<Entity*>& entities, Renderer* renderer, Window* window, FrameBuffer* framebuffer);
    };
}