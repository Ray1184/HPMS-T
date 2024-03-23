#include "ecs/system/RenderSystem.h"
#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/TilesPool.h"
#include "base/ResourcesHandler.h"

#include <sstream>
#include <utility>

void hpms::RenderSystem::Init(std::vector<Entity*>& entities, RenderSystemParams* args)
{
}

void hpms::RenderSystem::Update(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    auto* renderer = args->renderer;
    auto* window = args->window;
    auto* framebuffer = args->frameBuffer;

    std::vector<Drawable*> drawables;
    std::unordered_map<std::string, Movable*> transforms;
    std::vector<std::pair<std::string, Picture*> > pictures;
    std::vector<std::pair<std::string, Sprite*> > sprites;
    for (auto* entity: entities)
    {
        if (entity->IsChanged())
        {
            if (entity->HasComponent(COMPONENT_MOVABLE))
            {
                auto* mov = entity->GetComponent<Movable>(COMPONENT_MOVABLE);
                transforms[entity->GetId()] = mov;
            }
            if (entity->HasComponent(COMPONENT_PICTURE))
            {
                auto* pic = entity->GetComponent<Picture>(COMPONENT_PICTURE);
                pictures.emplace_back(entity->GetId(), pic);
                layersToUpdate.insert(pic->layer);
            }
            if (entity->HasComponent(COMPONENT_SPRITE))
            {
                auto* sprite = entity->GetComponent<Sprite>(COMPONENT_SPRITE);
                sprites.emplace_back(entity->GetId(), sprite);
                layersToUpdate.insert(sprite->layer);
            }
        }
        entity->SetChanged(false);
    }
    UpdateDrawables(transforms, pictures, sprites);
    for (auto& [fst, snd]: poolsCache)
    {
        drawables.push_back(snd);
    }
    for (auto& [fst, snd]: picturesCache)
    {
        drawables.push_back(snd);
    }
    layersToUpdate.clear();
    renderer->Render(window, framebuffer, &drawables);
}

void hpms::RenderSystem::Cleanup(std::vector<Entity*>& entities, RenderSystemParams* args)
{
    for (auto& [fst, snd]: poolsCache)
    {
        SAFE_DELETE(TilesPool, snd);
    }
    for (auto& [fst, snd]: picturesCache)
    {
        SAFE_DELETE(PictureQuad, snd);
    }
}

void hpms::RenderSystem::UpdateDrawables(const std::unordered_map<std::string, Movable*>& transforms, const std::vector<std::pair<std::string, Picture*> >& pictures, const std::vector<std::pair<std::string, Sprite*> >& sprites)
{
    std::unordered_map<unsigned int, std::vector<std::pair<std::string, Picture*> > > picturesByLayers;
    std::unordered_map<unsigned int, std::vector<std::pair<std::string, Sprite*> > > spritesByLayers;

    for (const auto& picMap: pictures)
    {
        if (layersToUpdate.contains(picMap.second->layer))
        {
            picturesByLayers[picMap.second->layer].push_back(picMap);
        }
    }
    for (const auto& sprite: sprites)
    {
        if (layersToUpdate.contains(sprite.second->layer))
        {
            spritesByLayers[sprite.second->layer].push_back(sprite);
        }
    }

    for (const auto& [fst, snd]: picturesByLayers)
    {
        for (const auto& [fst2, snd2]: snd)
        {
            Transform2D t2d{0, 0};
            if (transforms.contains(fst2))
            {
                const auto* mov = transforms.at(fst2);
                t2d = mov->position;
            }
            auto* tex = ResourcesHandler::Provide<Texture>(snd2->pakId, snd2->textureName);
            picturesCache[fst] = SAFE_NEW(PictureQuad, fst, tex, t2d, "/" + snd2->id);
            picturesCache[fst]->SetChanged(true);
        }
    }

    for (const auto& [fst, snd]: spritesByLayers)
    {
        auto spritesOnSameLayer = snd;
        auto* mergedTexture = MergeTextures(spritesOnSameLayer);
        poolsCache[fst] = SAFE_NEW(TilesPool, fst, mergedTexture, CreateMergedId(spritesOnSameLayer));
        poolsCache[fst]->SetChanged(true);
        for (const auto& [fst2, snd2]: spritesOnSameLayer)
        {
            Transform2D t2d{0, 0};
            if (transforms.contains(fst2))
            {
                const auto* mov = transforms.at(fst2);
                t2d = mov->position;
            }
            for (auto& tile: snd2->tiles)
            {
                tile.position.x += t2d.x;
                tile.position.y += t2d.y;
                poolsCache[fst]->AddTile(tile);
            }
        }
    }
}


std::string hpms::RenderSystem::CreateMergedId(const std::vector<std::pair<std::string, Sprite*> >& sprites)
{
    std::stringstream ss;
    for (const auto& [fst, snd]: sprites)
    {
        ss << "/" << snd->id;
    }
    return ss.str();
}


hpms::Texture* hpms::RenderSystem::MergeTextures(const std::vector<std::pair<std::string, Sprite*> >& sprites)
{
    // TODO merge textures
    const auto& [fst, snd] = sprites[0];
    return ResourcesHandler::Provide<Texture>(snd->pakId, snd->textureName);
}
