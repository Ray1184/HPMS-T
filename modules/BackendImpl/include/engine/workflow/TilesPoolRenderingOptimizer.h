#pragma once

#include "engine/renderable/TilesPool.h"
#include "engine/Window.h"
#include "engine/FrameBuffer.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace hpms
{
    class TilesPoolRenderingOptimizer
    {
    private:
        static bool InsideView(const Tile& tile, const sf::View& view, unsigned int ratio);

        static void RemoveOutOfView(const Window* window, const std::unordered_set<Tile>* in, std::vector<Tile>* out, sf::RenderWindow* const& sfWindow);

    public:
        static void Optimize(Window* window, const std::unordered_set<Tile>* in, std::vector<Tile>* out);


    };
}