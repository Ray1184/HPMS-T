#pragma once

#include "engine/Drawable.h"

namespace hpms
{
    struct Image
    {
        Transform2D position;
        float width;
        float height;
    };

    struct PictureData : public Drawable
    {
        Image image;


        PictureData(unsigned int layer, Texture* texture, Transform2D position, const std::string& id, int flags = STRATEGY_STATIC);


        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_PICTURE;
        }
    };
}
