#pragma once

#include "engine/renderable/TilesChunkData.h"
#include "engine/Drawable.h"
#include "engine/Tile.h"

namespace hpms
{
    struct SpriteData : public TilesChunkData
    {
        Transform2D position;
        int width{0};
        int height{0};

        SpriteData() = default;

        SpriteData(const std::string& id, const unsigned int layer, Texture* texture, const std::vector<Tile>& tiles, const Transform2D& position, const int width, const int height, const bool updateVertices = false) : TilesChunkData(id, layer, texture, tiles, updateVertices),
                                                                                                                                                                                                                                 position(position),
                                                                                                                                                                                                                                 width(width),
                                                                                                                                                                                                                                 height(height)
        {
        }

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_SPRITE;
        }
    };

    struct SpriteBatch : public Drawable
    {
        std::vector<SpriteData*> subSprites;

        SpriteBatch() = default;

        SpriteBatch(const std::string& id, const unsigned int layer, Texture* texture, const std::vector<SpriteData*>& subSprites, const bool updateVertices = false) : Drawable(id, layer, texture, updateVertices),
                                                                                                                                                                                     subSprites(subSprites)
        {
        }

        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_SPRITE;
        }
    };
}
