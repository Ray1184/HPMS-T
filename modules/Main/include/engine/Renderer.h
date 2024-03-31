#pragma once

#include "engine/Drawable.h"
#include "engine/Window.h"

#include <vector>

namespace hpms
{
    class Renderer
    {
    public:
        virtual void Render(Window* window, Transform2D& view, std::vector<Drawable*>* drawables) = 0;
    };
}