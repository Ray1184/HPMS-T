#pragma once

#include "engine/GameLogic.h"
#include "engine/renderable/PictureQuad.h"
#include "base/Utils.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "ecs/component/Components.h"
#include "ecs/system/Systems.h"
#include "ecs/SystemFactory.h"
#include "ecs/Entity.h"

#include <random>

#define MAP_SIZE 8

namespace hpms
{
    class TestLogic : public GameLogic
    {
    private:
        ResourceSupplierImpl* resSupplier;
        std::vector<Entity*> entities;
        Entity* viewEntity = nullptr;
        bool renderInit{false};

    public:
        [[noreturn]] virtual void Init() override
        {
            Logs::logLevel = TRACE;
            resSupplier = SAFE_NEW(hpms::ResourceSupplierImpl);
            ResourcesHandler::PreloadResources("pak1.zip", resSupplier);
            //auto* backTex = hpms::ResourcesHandler::Provide<hpms::Texture>("pak1.zip", "/textures/background.png");
            //auto* tilemapTex = hpms::ResourcesHandler::Provide<hpms::Texture>("pak1.zip", "/textures/tileset_custom_48_48.png");
            // auto* pic = SAFE_NEW(hpms::PictureQuad, 0, backTex, hpms::Transform2D{0, 0});
            auto* picEntity = SAFE_NEW(hpms::Entity, "pic_01");
            auto* compPic = SAFE_NEW(hpms::Picture);
            compPic->textureName = "/textures/background.png";
            compPic->pakId = "pak1.zip";
            compPic->layer = 0;
            compPic->id = Strings::UniqueId();
            picEntity->AddComponent(compPic);

            auto* mapEntity = SAFE_NEW(hpms::Entity, "map_01");
            auto* compMap = SAFE_NEW(hpms::TileMap);
            compMap->textureName = "/textures/tileset_custom_48_48.png";
            compMap->pakId = "pak1.zip";
            compMap->layer = 1;
            compMap->id = Strings::UniqueId();
            START_TIMER();
            FillChunkRandom(compMap, 1);
            END_TIMER();
            LOG_DEBUG("Large map loaded in {} seconds", elapsed.count());
            mapEntity->AddComponent(compMap);
            viewEntity = SAFE_NEW(hpms::Entity, "view_01");
            auto* compCam = SAFE_NEW(hpms::Camera);
            viewEntity->AddComponent(compCam);
            //auto* chunk1 = SAFE_NEW(hpms::TilesPool, 1, tilemapTex);
            //auto* chunk2 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk3 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk4 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk5 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk6 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk7 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk8 = SAFE_NEW(hpms::TilesPool);


            //FillChunkRandom(chunk2, 1);
            //FillChunkRandom(chunk3, 1);
            //FillChunkRandom(chunk4, 1);
            //FillChunkRandom(chunk5, 1);
            //FillChunkRandom(chunk6, 1);
            //FillChunkRandom(chunk7, 1);
            //FillChunkRandom(chunk8, 1);

            entities.push_back(picEntity);
            entities.push_back(mapEntity);
            entities.push_back(viewEntity);
            //drawables.push_back(chunk1);
            //drawables.push_back(chunk2);
            //drawables.push_back(chunk3);
            //drawables.push_back(chunk4);
            //drawables.push_back(chunk5);
            //drawables.push_back(chunk6);
            //drawables.push_back(chunk7);
            //drawables.push_back(chunk8);
        }

        void FillChunkRandom(TileMap* tmap, int iter) const
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            // Definisci la distribuzione per generare numeri tra 0 e 2 (inclusi)
            std::uniform_int_distribution<int> distribution(-1, 5);

            for (int n = 0; n < iter; n++)
            {
                for (int x = 0; x < MAP_SIZE * 1000; x++)
                {
                    for (int y = 0; y < MAP_SIZE * 1000; y++)
                    {
                        //for (int z = -8; z < 8; z++)
                        {
                            int randomX = 1; //distribution(gen);
                            int randomY = 1; //distribution(gen);
                            int randomZ = 1; //distribution(gen);
                            Tile tile{(float) x * randomX, (float) y * randomY, 0, 0};
                            const int chunkX = static_cast<int>(tile.position.x) / CHUNK_SIZE;
                            const int chunkY = static_cast<int>(tile.position.y) / CHUNK_SIZE;
                            Transform2D key{static_cast<float>(chunkX), static_cast<float>(chunkY)};
                            tmap->chunks[key].push_back(tile);
                        }
                    }
                }
            }
        }

        void HandleInput(InputHandler* inputHandler) override
        {
        }

        void Update(float tpf) override
        {
            auto* cam = viewEntity->GetComponent<Camera>(COMPONENT_CAMERA);
            cam->position.x = cam->position.x + (tpf * 100);
            cam->position.y = cam->position.y + (tpf * 30);
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
