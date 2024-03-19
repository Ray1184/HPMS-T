#include "engine/renderable/TilesPool.h"

hpms::TilesPool::TilesPool(unsigned int layer, hpms::Texture* texture)
{
    this->layer = layer;
    this->texture = texture;
    this->id = hpms::Strings::UniqueId();
}

std::unordered_set<hpms::Tile>* hpms::TilesPool::GetTiles()
{
    return &tiles;
}

void hpms::TilesPool::AddTile(hpms::Tile& t)
{
    SetChanged(true);
    float s = TILE_SIZE;
    float px = t.position.transform2D.x * s;
    float py = s * t.position.transform2D.y - s * t.position.z;
    t.screenPosition = {px, py};
    tiles.insert(t);
}

