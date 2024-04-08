#include "engine/renderable/TilesPool.h"

hpms::TilesPool::TilesPool()
{}

hpms::TilesPool::TilesPool(const unsigned int layer, Texture* texture, const std::string& id, const std::vector<Tile>& tiles, const int flags)
{
    this->layer = layer;
    this->texture = texture;
    this->id = id;
    this->tiles = tiles;
    updateVertices = flags & STRATEGY_UPDATE_VERTICES;
}
