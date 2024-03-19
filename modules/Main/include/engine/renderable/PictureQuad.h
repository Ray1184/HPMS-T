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

    class PictureQuad : public hpms::Drawable
    {
    private:
        std::string id;
        hpms::Image image;

    public:
        PictureQuad(unsigned int layer, Texture* texture, Transform2D position);

        Image* GetImage();

        [[nodiscard]] inline RenderType GetType() const override
        {
            return RenderType::DRAWABLE_PICTURE;
        }

        [[nodiscard]] inline const std::string GetId() const override
        {
            return "PictureQuad/" + id;
        }
    };
}