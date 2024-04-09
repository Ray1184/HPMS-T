#include "engine/renderable/SpriteData.h"

hpms::SpriteData::SpriteData(const unsigned int layer, Texture* texture, const std::string& id, Transform2D position, const std::vector<Tile>& tiles, int width, int height, int flags)
{
    this->layer = layer;
    this->texture = texture;
    this->id = id;
    this->position = position;
    this->tiles = tiles;
    this->width = width;
    this->height = height;
    updateVertices = flags & STRATEGY_UPDATE_VERTICES;
}
