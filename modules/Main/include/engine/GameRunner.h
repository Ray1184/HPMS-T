#pragma once

#include "engine/Window.h"
#include "engine/GameLogic.h"

namespace hpms
{
    class GameRunner
    {
    public:
        virtual void Run() = 0;
    };
}