#pragma once

#include "engine/GameRunner.h"

namespace hpms
{
    class GameRunnerImpl : public GameRunner
    {
    private:
        hpms::Window* window;
        hpms::GameLogic* logic;
        hpms::InputHandler* inputHandler;
        hpms::Renderer* renderer;
    public:
        GameRunnerImpl(Window* window, GameLogic* logic, InputHandler* inputHandler, Renderer* renderer);

        virtual void Run() override;
    };
}
