#include "engine/renderable/TilesPool.h"

hpms::TilesPool::TilesPool(const unsigned int layer, Texture* texture, const std::string& id)
{
    this->layer = layer;
    this->texture = texture;
    this->id = id;
}

std::unordered_set<hpms::Tile>* hpms::TilesPool::GetTiles()
{
    return &tiles;
}

void hpms::TilesPool::AddTile(const Tile& tile)
{
    SetChanged(true);
    tiles.insert(tile);
}

