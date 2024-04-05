#include "ecs/system/RenderSystem.h"

#include <ranges>

#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/TilesPool.h"
#include "base/ResourcesHandler.h"
#include "base/Math.h"

#include <utility>

void hpms::RenderSystem::Init(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    InitView(entities, args);
    InitChunks(entities, args);
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

    for (auto& val: allChunks | std::views::values)
    {
        SAFE_DELETE(TilesPool, val);
    }
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
        const auto* tileMap = snd.second;
        auto* mergedTexture = ResourcesHandler::Provide<Texture>(tileMap->pakId, tileMap->textureName);

        int counter = 0;
        for (const auto& tile: tileMap->tiles)
        {
            const int chunkX = static_cast<int>(tile.position.x) / CHUNK_SIZE;
            const int chunkY = static_cast<int>(tile.position.y) / CHUNK_SIZE;
            Transform2D key{static_cast<float>(chunkX), static_cast<float>(chunkY)};
            if (!allChunks.contains(key))
            {
                allChunks[key] = SAFE_NEW(TilesPool, fst, mergedTexture, tileMap->id + "_C_" + std::to_string(counter++));
            }
            allChunks[key]->AddTile(tile);
        }
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

    const auto width = static_cast<float>(args->window->GetSettings().width);
    const auto height = static_cast<float>(args->window->GetSettings().height);
    const AABox viewRect{view.x, view.y, width, height};
    for (auto& [fst, snd]: allChunks)
    {
        const Transform2D chunkCoord = fst;
        const AABox chunkBox{chunkCoord.x * TILE_SIZE * CHUNK_SIZE, chunkCoord.y * TILE_SIZE * CHUNK_SIZE, TILE_SIZE * CHUNK_SIZE, TILE_SIZE * CHUNK_SIZE};
        if (Math::Intersect(chunkBox, viewRect))
        {
            inViewChunks.push_back(snd);
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

            const AABox picBox{pos.x, pos.y, allPictures[pic->id]->GetImage()->width, allPictures[pic->id]->GetImage()->height};
            if (pic->visible && Math::Intersect(picBox, viewRect))
            {
                inViewPictures.push_back(allPictures[pic->id]);
            }
        }
    }
}
