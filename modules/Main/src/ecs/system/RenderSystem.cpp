#include "ecs/system/RenderSystem.h"

#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/TilesPool.h"
#include "base/ResourcesHandler.h"
#include "base/Math.h"

#include <ranges>
#include <utility>

void hpms::RenderSystem::Init(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    START_TIMER();
    InitView(entities, args);
    InitChunks(entities, args);
    END_TIMER();
    LOG_DEBUG("RenderSystem initialized in {} seconds", elapsed.count());
}

void hpms::RenderSystem::Update(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    UpdateChunks(entities, args);
    UpdateDrawables(entities, args);
    std::vector<Drawable*> drawables;
    drawables.insert(drawables.end(), inViewChunks.begin(), inViewChunks.end());
    drawables.insert(drawables.end(), inViewSprites.begin(), inViewSprites.end());
    drawables.insert(drawables.end(), inViewPictures.begin(), inViewPictures.end());
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }
    args->renderer->Render(args->window, view, &drawables);
}


void hpms::RenderSystem::Cleanup(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    for (auto& val: allSprites | std::views::values)
    {
        SAFE_DELETE(SimpleSprite, val);
    }
    for (auto& val: allPictures | std::views::values)
    {
        SAFE_DELETE(PictureQuad, val);
    }
    for (auto & [fst, snd] : pooledChunkData)
    {
        snd.clear();
    }

    allSprites.clear();
    allPictures.clear();
    pooledChunkData.clear();

}

void hpms::RenderSystem::InitView(const std::vector<Entity*>& entities, RenderSystemParams* args)
{
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_CAMERA))
        {
            cam = entity->GetComponent<Camera>(COMPONENT_CAMERA);
        }
    }
}

void hpms::RenderSystem::InitChunks(const std::vector<Entity*>& entities, RenderSystemParams* args)
{
    std::unordered_map<unsigned int, std::pair<std::string, TileMap*> > tileMapsByLayer;
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_TILEMAP))
        {
            auto* tileMap = entity->GetComponent<TileMap>(COMPONENT_TILEMAP);
            tileMapsByLayer[tileMap->layer] = {entity->GetId(), tileMap};
        }
    }

    for (const auto& [fst, snd]: tileMapsByLayer)
    {
        START_TIMER();
        const auto* tileMap = snd.second;
        auto* texture = ResourcesHandler::Provide<Texture>(tileMap->pakId, tileMap->textureName);
        auto& chunks = tileMap->chunks;
        pooledChunkData[fst].reserve(chunks.size());

        for (const auto& [fst2, snd2]: chunks)
        {
            TilesPool tilesPool;
            tilesPool.layer = fst;
            tilesPool.texture = texture;
            tilesPool.id = "L_" + std::to_string(fst) + "_" + tileMap->id + "_C_" + std::to_string(fst2.x) + "_" + std::to_string(fst2.y);
            tilesPool.tiles = snd2;
            allChunks[fst2] = &pooledChunkData[fst].emplace_back(std::move(tilesPool));
        }
        END_TIMER();
        LOG_DEBUG("{} Chunks allocation done in {} seconds for layer {}", allChunks.size(), elapsed.count(), fst);
    }
}

void hpms::RenderSystem::UpdateChunks(const std::vector<Entity*>& entities, RenderSystemParams* args)
{
    inViewChunks.clear();
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }

    const float chunkX = std::floor(view.x / (TILE_SIZE * CHUNK_SIZE));
    const float chunkY = std::floor(view.y / (TILE_SIZE * CHUNK_SIZE));
    Transform2D faces[9];
    faces[0] = Transform2D{chunkX - 1, chunkY - 1};
    faces[1] = Transform2D{chunkX - 1, chunkY};
    faces[2] = Transform2D{chunkX - 1, chunkY + 1};
    faces[3] = Transform2D{chunkX, chunkY - 1};
    faces[4] = Transform2D{chunkX, chunkY};
    faces[5] = Transform2D{chunkX, chunkY + 1};
    faces[6] = Transform2D{chunkX + 1, chunkY - 1};
    faces[7] = Transform2D{chunkX + 1, chunkY};
    faces[8] = Transform2D{chunkX + 1, chunkY + 1};

    for (auto& face: faces)
    {
        if (allChunks.contains(face))
        {
            inViewChunks.push_back(allChunks[face]);
        }
    }
}


void hpms::RenderSystem::UpdateDrawables(const std::vector<Entity*>& entities, RenderSystemParams* args)
{
    inViewSprites.clear();
    inViewPictures.clear();
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }
    const auto width = static_cast<float>(args->window->GetSettings().width);
    const auto height = static_cast<float>(args->window->GetSettings().height);
    const AABox viewRect{view.x, view.y, width, height};

    std::unordered_map<unsigned int, std::pair<std::string, TileMap*> > tileMapsByLayer;
    for (auto* entity: entities)
    {
        Transform2D pos{0, 0};
        if (entity->HasComponent(COMPONENT_MOVABLE))
        {
            const auto* mov = entity->GetComponent<Movable>(COMPONENT_MOVABLE);
            pos.x = mov->position.x;
            pos.y = mov->position.y;
        }

        if (entity->HasComponent(COMPONENT_SPRITE))
        {
            const auto* sprite = entity->GetComponent<Sprite>(COMPONENT_SPRITE);

            if (!allSprites.contains(sprite->id))
            {
                auto* tex = ResourcesHandler::Provide<Texture>(sprite->pakId, sprite->textureName);
                allSprites[sprite->id] = SAFE_NEW(SimpleSprite, sprite->layer, tex, sprite->id, pos, sprite->tiles, sprite->width, sprite->height, STRATEGY_UPDATE_VERTICES);
            }

            const AABox spriteBox{pos.x, pos.y, static_cast<float>(sprite->width), static_cast<float>(sprite->height)};
            if (sprite->visible && Math::Intersect(spriteBox, viewRect))
            {
                inViewSprites.push_back(allSprites[sprite->id]);
            }
        }

        if (entity->HasComponent(COMPONENT_PICTURE))
        {
            const auto* pic = entity->GetComponent<Picture>(COMPONENT_PICTURE);

            if (!allPictures.contains(pic->id))
            {
                auto* tex = ResourcesHandler::Provide<Texture>(pic->pakId, pic->textureName);
                allPictures[pic->id] = SAFE_NEW(PictureQuad, pic->layer, tex, pos, pic->id);
            }

            const AABox picBox{pos.x, pos.y, allPictures[pic->id]->image.width, allPictures[pic->id]->image.height};
            if (pic->visible && Math::Intersect(picBox, viewRect))
            {
                inViewPictures.push_back(allPictures[pic->id]);
            }
        }
    }
}
