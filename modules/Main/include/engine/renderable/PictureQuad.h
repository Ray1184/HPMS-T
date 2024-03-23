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
        PictureQuad(unsigned int layer, Texture* texture, Transform2D position, const std::string& id);

        Image* GetImage();

        [[nodiscard]] RenderType GetType() const override
        {
            return RenderType::DRAWABLE_PICTURE;
        }

        [[nodiscard]] const std::string GetId() const override
        {
            return "PictureQuad" + id;
        }
    };
}