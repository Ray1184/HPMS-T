#pragma once

#include "engine/Renderer.h"
#include "engine/InputHandler.h"

namespace hpms
{
    class GameLogic
    {
    public:
        virtual void Init() = 0;
        virtual void HandleInput(hpms::InputHandler* inputHandler) = 0;
        virtual void Update(float tpf) = 0;
        virtual void Render(Renderer* renderer, Window* window) = 0;
        virtual void Cleanup() = 0;
    };
}