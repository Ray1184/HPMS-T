#include "engine/renderable/PictureQuad.h"

hpms::PictureQuad::PictureQuad(const unsigned int layer, Texture* texture, const Transform2D position, const std::string& id, int flags)
{
    this->layer = layer;
    this->texture = texture;
    this->image.position = position;
    image.width = static_cast<float>(texture->Width());
    image.height = static_cast<float>(texture->Height());
    this->id = id;
    updateVertices = flags & STRATEGY_UPDATE_VERTICES;
}

hpms::Image* hpms::PictureQuad::GetImage()
{
    return &image;
}

