#pragma once

#include "engine/GameLogic.h"
#include "engine/renderable/PictureData.h"
#include "base/Utils.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "ecs/component/Components.h"
#include "ecs/system/Systems.h"
#include "ecs/SystemFactory.h"
#include "ecs/Entity.h"

#include <random>

#define MAP_SIZE_CHUNKS 64

namespace hpms
{
    class TestLogic : public GameLogic
    {
    private:
        ResourceSupplierImpl* resSupplier;
        std::vector<Entity*> entities;
        std::vector<Entity*> sprites;
        Entity* viewEntity = nullptr;
        Entity* picEntity = nullptr;
        Entity* spritEntity = nullptr;
        Entity* spritEntity2 = nullptr;
        bool renderInit{false};

    public:


        [[noreturn]] virtual void Init() override
        {
            Logs::logLevel = TRACE;
            resSupplier = SAFE_NEW(hpms::ResourceSupplierImpl);
            ResourcesHandler::PreloadResources("pak1.zip", resSupplier);
            picEntity = SAFE_NEW(hpms::Entity, "pic_01");
            auto* compPic = SAFE_NEW(hpms::Picture);
            compPic->textureName = "/textures/background.png";
            compPic->pakId = "pak1.zip";
            compPic->layer = 5;
            compPic->id = Strings::UniqueId();
            compPic->picture.id = compPic->id;
            compPic->picture.layer = compPic->layer;
            compPic->picture.texture = ResourcesHandler::Provide<Texture>(compPic->pakId, compPic->textureName);
            compPic->picture.width = compPic->picture.texture->Width();
            compPic->picture.height = compPic->picture.texture->Height();
            picEntity->AddComponent(compPic);

            //auto* compMov = SAFE_NEW(hpms::Movable);
            //compMov->position = Transform2D{50, 50};
            //picEntity->AddComponent(compMov);





            auto* mapEntity = SAFE_NEW(hpms::Entity, "map_01");
            auto* compMap = SAFE_NEW(hpms::TilesMap);
            compMap->textureName = "/textures/tileset_custom_48_48.png";
            compMap->pakId = "pak1.zip";
            compMap->layer = 0;
            compMap->id = Strings::UniqueId();
            START_TIMER(test);
            FillChunkRandom(compMap);
            END_TIMER(test);
            LOG_DEBUG("Large map loaded in {} seconds", GET_ELAPSED(test));
            mapEntity->AddComponent(compMap);

            viewEntity = SAFE_NEW(hpms::Entity, "view_01");
            auto* compCam = SAFE_NEW(hpms::Camera);
            viewEntity->AddComponent(compCam);

            entities.push_back(picEntity);
            entities.push_back(mapEntity);
            entities.push_back(viewEntity);
            for (int i = 0; i < 1024; i++)
            {
                auto* spriteEnt = GenerateRandomSprite();
                entities.push_back(spriteEnt);
                sprites.push_back(spriteEnt);
            }
            //entities.push_back(spritEntity);
            //entities.push_back(spritEntity2);
        }

        Entity* GenerateRandomSprite()
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            // Definisci la distribuzione per generare numeri tra 0 e 2 (inclusi)
            std::uniform_int_distribution<int> distribution(-10, 320);
            int tx = distribution(gen);
            int ty = distribution(gen);

            auto* spriteEntity = SAFE_NEW(hpms::Entity, "sprite_01");
            auto* compSprite = SAFE_NEW(hpms::Sprite);
            compSprite->textureName = "/textures/sprite_1.png";
            compSprite->pakId = "pak1.zip";
            compSprite->layer = 10;
            compSprite->id = Strings::UniqueId();
            compSprite->sprite.id = compSprite->id;
            compSprite->sprite.layer = compSprite->layer;
            compSprite->sprite.texture = ResourcesHandler::Provide<Texture>(compSprite->pakId, compSprite->textureName);
            compSprite->sprite.tiles.push_back({{0, 0}, {0, 0}});
            compSprite->sprite.tiles.push_back({{1, 0}, {1, 0}});
            compSprite->sprite.tiles.push_back({{0, 1}, {0, 1}});
            compSprite->sprite.tiles.push_back({{1, 1}, {1, 1}});
            compSprite->sprite.tiles.push_back({{0, 2}, {0, 2}});
            compSprite->sprite.tiles.push_back({{1, 2}, {1, 2}});
            compSprite->sprite.tiles.push_back({{0, 3}, {0, 3}});
            compSprite->sprite.tiles.push_back({{1, 3}, {1, 3}});
            spriteEntity->AddComponent(compSprite);
            auto* compMovSp = SAFE_NEW(hpms::Movable);
            compMovSp->position = Transform2D{(float)tx, (float)ty};
            spriteEntity->AddComponent(compMovSp);
            return spriteEntity;
        }

        void FillTiles(TilesChunkData* data, int x, int y) const
        {
            for (int i = 0; i < CHUNK_SIZE; i++)
            {
                for (int j = 0; j < CHUNK_SIZE; j++)
                {
                    Tile tile;
                    tile.position = Transform2D{i + x * CHUNK_SIZE * 1.0f, j + y * CHUNK_SIZE * 1.0f};
                    tile.texCoords = Transform2D{0, 0};
                    data->tiles.push_back(tile);
                }
            }
        }

        void FillChunkRandom(TilesMap* tmap) const
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            // Definisci la distribuzione per generare numeri tra 0 e 2 (inclusi)
            std::uniform_int_distribution<int> distribution(-1, 5);

            for (int x = 0; x < MAP_SIZE_CHUNKS; x++)
            {
                for (int y = 0; y < MAP_SIZE_CHUNKS; y++)
                {
                    TilesChunkData data;
                    data.id = "L" + std::to_string(tmap->layer) + "_C" + tmap->id + "[" + std::to_string(x) + "," + std::to_string(y) + "]";
                    data.layer = tmap->layer;
                    data.texture = ResourcesHandler::Provide<Texture>(tmap->pakId, tmap->textureName);
                    FillTiles(&data, x, y);
                    Transform2D k = {x * 1.0f, y * 1.0f};
                    tmap->chunks[k] = std::move(data);
                }
            }

        }

        void HandleInput(InputHandler* inputHandler) override
        {
        }

        void Update(float tpf) override
        {
            auto* cam = viewEntity->GetComponent<Camera>(COMPONENT_CAMERA);
            cam->position.x = cam->position.x + (tpf * 2);
            cam->position.y = cam->position.y + (tpf * 5);

            int i = 0;
            for (auto* sprite : sprites)
            {
                if (i == 0)
                {
                    auto* pos = sprite->GetComponent<Movable>(COMPONENT_MOVABLE);
                    pos->position.x = pos->position.x + (tpf * -3);
                    pos->position.y = pos->position.y + (tpf * 5);
                    //pos->changed = true;
                    i++;
                }
                //pos->changed = true;
            }
            //auto* pos = spritEntity->GetComponent<Movable>(COMPONENT_MOVABLE);
            //pos->position.x = pos->position.x * (tpf * -3);
            //pos->position.y = pos->position.y + (tpf * 5);
        }

        void Render(Renderer* renderer, Window* window) override
        {
            System<RenderSystemParams>* rs = SystemFactory::GetSystem<RenderSystemParams>(SYSTEM_RENDERER);
            RenderSystemParams params{renderer, window};
            if (!renderInit)
            {
                rs->Init(entities, &params);
                renderInit = true;
            }
            rs->Update(entities, &params);
            //renderer->Render(window, framebuffer, &drawables);
        }

        void Cleanup() override
        {
            System<RenderSystemParams>* rs = SystemFactory::GetSystem<RenderSystemParams>(SYSTEM_RENDERER);
            std::vector<Entity*> dummy;
            rs->Cleanup(dummy, nullptr);
            VertexBufferProvider::ClearAllBuffers();
            for (auto* entity: entities)
            {
                entity->ForeachComponent([](ComponentType t, Component* c)
                {
                    SAFE_DELETE(Component, c);
                });
                SAFE_DELETE(hpms::Entity, entity);
            }

            ResourcesHandler::UnloadResources("pak1.zip", resSupplier);
            SAFE_DELETE(hpms::ResourceSupplierImpl, resSupplier);
        }
    };
}
