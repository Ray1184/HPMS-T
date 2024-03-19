#pragma once

#include "engine/GameRunner.h"

namespace hpms
{
    class GameRunnerImpl : public GameRunner
    {
    private:
        hpms::Window* window;
        hpms::FrameBuffer* framebuffer;
        hpms::GameLogic* logic;
        hpms::InputHandler* inputHandler;
        hpms::Renderer* renderer;
    public:
        GameRunnerImpl(Window* window, FrameBuffer* framebuffer, GameLogic* logic, InputHandler* inputHandler, Renderer* renderer);

        virtual void Run() override;
    };
}
