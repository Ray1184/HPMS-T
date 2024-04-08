#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <bitset>

namespace hpms
{
    struct SimpleSprite : public Drawable
    {
        Transform2D position;
        int width;
        int height;
        std::vector<Tile> tiles;

        SimpleSprite(unsigned int layer, Texture* texture, const std::string& id, Transform2D position, const std::vector<Tile>& tiles, int width, int height, int flags = STRATEGY_STATIC);

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_SIMPLE_SPRITE;
        }
    };
}
