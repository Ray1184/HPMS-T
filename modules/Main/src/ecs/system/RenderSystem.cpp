#include "ecs/system/RenderSystem.h"
#include "base/ResourcesHandler.h"

#include <ranges>

void hpms::RenderSystem::Init(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    START_TIMER(RenderSystem_Init);
    InitView(entities);
    InitChunks(entities);
    InitSprites(entities);
    InitPictures(entities);
    END_TIMER(RenderSystem_Init);
    LOG_DEBUG("RenderSystem initialized in {} seconds", GET_ELAPSED(RenderSystem_Init));
}

void hpms::RenderSystem::Update(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }
    Transform2D faces[9];
    FindNearestFaces(view, faces);
    UpdatePositions(entities);
    UpdateChunks();
    UpdateSprites();
    UpdatePictures();
    std::vector<Drawable*> drawables;
    drawables.insert(drawables.end(), inViewChunks.begin(), inViewChunks.end());
    drawables.insert(drawables.end(), inViewPictures.begin(), inViewPictures.end());
    std::unordered_map<std::string, SpriteBatch> compositeSpritesByLayerAndTexture;
    for (auto* sprite: inViewSprites)
    {
        std::string key = "L" + std::to_string(sprite->layer) + "_SB_" + sprite->texture->ResourceId();
        compositeSpritesByLayerAndTexture[key].id = key;
        compositeSpritesByLayerAndTexture[key].subSprites.push_back(sprite);
        compositeSpritesByLayerAndTexture[key].layer = sprite->layer;
    }
    for (auto& snd: compositeSpritesByLayerAndTexture | std::views::values)
    {
        drawables.push_back(&snd);
    }
    args->renderer->Render(args->window, view, &drawables);
}


void hpms::RenderSystem::Cleanup(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    allSprites.clear();
    allPictures.clear();
    allChunks.clear();
}

void hpms::RenderSystem::InitView(const std::vector<Entity*>& entities)
{
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_CAMERA))
        {
            cam = entity->GetComponent<Camera>(COMPONENT_CAMERA);
        }
    }
}

void hpms::RenderSystem::InitChunks(const std::vector<Entity*>& entities)
{
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_TILES_MAP))
        {
            START_TIMER(RenderSystem_InitChunks);
            auto* tileMap = entity->GetComponent<TilesMap>(COMPONENT_TILES_MAP);
            allChunks[tileMap->layer] = tileMap;
            END_TIMER(RenderSystem_InitChunks);
            LOG_DEBUG("{} Chunks allocation done in {} seconds for layer {}", tileMap->chunks.size(), GET_ELAPSED(RenderSystem_InitChunks), tileMap->layer);
        }
    }
}

void hpms::RenderSystem::InitSprites(const std::vector<Entity*>& entities)
{
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_SPRITE))
        {
            auto* sprite = entity->GetComponent<Sprite>(COMPONENT_SPRITE);
            allSprites[sprite->layer].push_back(sprite);
        }
    }
}

void hpms::RenderSystem::InitPictures(const std::vector<Entity*>& entities)
{
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_PICTURE))
        {
            auto* pic = entity->GetComponent<Picture>(COMPONENT_PICTURE);
            allPictures[pic->layer] = pic;
        }
    }
}

void hpms::RenderSystem::UpdateChunks()
{
    inViewChunks.clear();
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }

    Transform2D faces[9];
    FindNearestFaces(view, faces);

    for (auto& face: faces)
    {
        for (auto& snd: allChunks | std::views::values)
        {
            auto& chunks = snd->chunks;
            if (chunks.contains(face))
            {
                auto* chunk = &chunks[face];
                inViewChunks.push_back(chunk);
            }
        }
    }
}

void hpms::RenderSystem::UpdateSprites()
{
    inViewSprites.clear();
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }

    Transform2D faces[9];
    FindNearestFaces(view, faces);

    for (auto& face: faces)
    {
        for (const auto& snd: allSprites | std::views::values)
        {
            for (const auto& sp: snd)
                if (sp->key == face)
                {
                    auto* sprite = &sp->sprite;
                    inViewSprites.push_back(sprite);
                }
        }
    }
}

void hpms::RenderSystem::UpdatePictures()
{
    inViewPictures.clear();
    Transform2D view{0, 0};
    if (cam != nullptr)
    {
        view.x = cam->position.x;
        view.y = cam->position.y;
    }

    Transform2D faces[9];
    FindNearestFaces(view, faces);

    for (auto& face: faces)
    {
        for (const auto& snd: allPictures | std::views::values)
        {
            if (snd->key == face)
            {
                auto* picture = &snd->picture;
                inViewPictures.push_back(picture);
            }
        }
    }
}

void hpms::RenderSystem::FindNearestFaces(const Transform2D& view, Transform2D (& faces)[9])
{
    const float chunkX = std::floor(view.x / (TILE_SIZE * CHUNK_SIZE));
    const float chunkY = std::floor(view.y / (TILE_SIZE * CHUNK_SIZE));
    faces[0] = Transform2D{chunkX - 1, chunkY - 1};
    faces[1] = Transform2D{chunkX - 1, chunkY};
    faces[2] = Transform2D{chunkX - 1, chunkY + 1};
    faces[3] = Transform2D{chunkX, chunkY - 1};
    faces[4] = Transform2D{chunkX, chunkY};
    faces[5] = Transform2D{chunkX, chunkY + 1};
    faces[6] = Transform2D{chunkX + 1, chunkY - 1};
    faces[7] = Transform2D{chunkX + 1, chunkY};
    faces[8] = Transform2D{chunkX + 1, chunkY + 1};
}

void hpms::RenderSystem::UpdatePositions(const std::vector<Entity*>& entities)
{
    for (auto* entity: entities)
    {
        if (entity->HasComponent(COMPONENT_MOVABLE))
        {
            if (auto* mov = entity->GetComponent<Movable>(COMPONENT_MOVABLE))
            {

                if (entity->HasComponent(COMPONENT_SPRITE))
                {
                    auto* sprite = entity->GetComponent<Sprite>(COMPONENT_SPRITE);
                    sprite->key.x = std::floor(mov->position.x / (TILE_SIZE * CHUNK_SIZE));
                    sprite->key.y = std::floor(mov->position.y / (TILE_SIZE * CHUNK_SIZE));
                    sprite->sprite.position.x = mov->position.x;
                    sprite->sprite.position.y = mov->position.y;
                    sprite->sprite.updateVertices = true;
                }
                if (entity->HasComponent(COMPONENT_PICTURE))
                {
                    auto* pic = entity->GetComponent<Picture>(COMPONENT_PICTURE);
                    pic->key.x = std::floor(mov->position.x / (TILE_SIZE * CHUNK_SIZE));
                    pic->key.y = std::floor(mov->position.y / (TILE_SIZE * CHUNK_SIZE));
                    pic->picture.position.x = mov->position.x;
                    pic->picture.position.y = mov->position.y;
                    pic->picture.updateVertices = true;
                }
            }
        }
    }
}
