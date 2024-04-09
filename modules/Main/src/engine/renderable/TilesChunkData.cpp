#include "engine/renderable/TilesChunkData.h"

hpms::TilesChunkData::TilesChunkData(const unsigned int layer, Texture* texture, const std::string& id, const std::vector<Tile>& tiles, const int flags)
{
    this->layer = layer;
    this->texture = texture;
    this->id = id;
    this->tiles = tiles;
    updateVertices = flags & STRATEGY_UPDATE_VERTICES;
}
