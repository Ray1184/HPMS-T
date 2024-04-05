#pragma once

#include "engine/Drawable.h"
#include "engine/Tile.h"

#include <bitset>

namespace hpms
{
    class SimpleSprite : public Drawable
    {
    private:
        Transform2D position;
        int width;
        int height;
        std::vector<Tile> tiles;

    public:
        SimpleSprite(unsigned int layer, Texture* texture, const std::string& id, Transform2D position, const std::vector<Tile>& tiles, int width, int height, int flags = STRATEGY_STATIC);

        std::vector<Tile>* GetTiles();

        [[nodiscard]] int GetHeight() const
        {
            return height;
        }

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_SIMPLE_SPRITE;
        }
    };
}
