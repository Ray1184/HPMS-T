#include "engine/renderable/PictureQuad.h"

hpms::PictureQuad::PictureQuad(unsigned int layer, hpms::Texture* texture, hpms::Transform2D position)
{
    this->layer = layer;
    this->texture = texture;
    this->image.position = position;
    image.width = static_cast<float>(texture->Width());
    image.height = static_cast<float>(texture->Height());
    this->id = hpms::Strings::UniqueId();
}

hpms::Image* hpms::PictureQuad::GetImage()
{
    return &image;
}

