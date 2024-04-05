#include "engine/renderable/TilesPool.h"

hpms::TilesPool::TilesPool(const unsigned int layer, Texture* texture, const std::string& id, const int flags)
{
    this->layer = layer;
    this->texture = texture;
    this->id = id;
    updateVertices = flags & STRATEGY_UPDATE_VERTICES;
}

std::vector<hpms::Tile>* hpms::TilesPool::GetTiles()
{
    return &tiles;
}

void hpms::TilesPool::AddTile(const Tile& tile)
{
    tiles.push_back(tile);
}

