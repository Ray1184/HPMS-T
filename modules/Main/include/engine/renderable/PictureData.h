#pragma once

#include "engine/Drawable.h"

namespace hpms
{
    struct PictureData : public Drawable
    {
        Transform2D position;
        float width{0};
        float height{0};

        PictureData() = default;

        PictureData(const std::string& id, const unsigned int layer, Texture* texture, const Transform2D& position, const bool updateVertices = false) : Drawable(id, layer, texture, updateVertices)
        {
            this->position = position;
            width = static_cast<float>(texture->Width());
            height = static_cast<float>(texture->Height());
        }


        [[nodiscard]] RenderType GetType() const override
        {
            return DRAWABLE_PICTURE;
        }
    };
}
