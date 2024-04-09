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

#define MAP_SIZE_CHUNKS 256

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
            // auto* pic = SAFE_NEW(hpms::PictureData, 0, backTex, hpms::Transform2D{0, 0});
            auto* picEntity = SAFE_NEW(hpms::Entity, "pic_01");
            auto* compPic = SAFE_NEW(hpms::Picture);
            compPic->textureName = "/textures/background.png";
            compPic->pakId = "pak1.zip";
            compPic->layer = 0;
            compPic->id = Strings::UniqueId();
            picEntity->AddComponent(compPic);

            auto* mapEntity = SAFE_NEW(hpms::Entity, "map_01");
            auto* compMap = SAFE_NEW(hpms::TilesMap);
            compMap->textureName = "/textures/tileset_custom_48_48.png";
            compMap->pakId = "pak1.zip";
            compMap->layer = 1;
            compMap->id = Strings::UniqueId();
            START_TIMER();
            FillChunkRandom(compMap);
            END_TIMER();
            LOG_DEBUG("Large map loaded in {} seconds", GET_ELAPSED());
            mapEntity->AddComponent(compMap);
            viewEntity = SAFE_NEW(hpms::Entity, "view_01");
            auto* compCam = SAFE_NEW(hpms::Camera);
            viewEntity->AddComponent(compCam);
            //auto* chunk1 = SAFE_NEW(hpms::TilesChunkData, 1, tilemapTex);
            //auto* chunk2 = SAFE_NEW(hpms::TilesChunkData);
            //auto* chunk3 = SAFE_NEW(hpms::TilesChunkData);
            //auto* chunk4 = SAFE_NEW(hpms::TilesChunkData);
            //auto* chunk5 = SAFE_NEW(hpms::TilesChunkData);
            //auto* chunk6 = SAFE_NEW(hpms::TilesChunkData);
            //auto* chunk7 = SAFE_NEW(hpms::TilesChunkData);
            //auto* chunk8 = SAFE_NEW(hpms::TilesChunkData);


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
                    data.tempData["TEXTURE_NAME"] = tmap->textureName;
                    data.tempData["PAK_ID"] = tmap->pakId;
                    FillTiles(&data, x, y);
                    Transform2D k = {x * 1.0f, y * 1.0f};
                    tmap->chunks[k] = std::move(data);
                }
            }

            //for (int n = 0; n < iter; n++)
            //{
            //    for (int x = 0; x < MAP_SIZE * 1000; x++)
            //    {
            //        for (int y = 0; y < MAP_SIZE * 1000; y++)
            //        {
            //            //for (int z = -8; z < 8; z++)
            //            {
            //                int randomX = 1; //distribution(gen);
            //                int randomY = 1; //distribution(gen);
            //                int randomZ = 1; //distribution(gen);
            //                Tile tile{(float) x * randomX, (float) y * randomY, 0, 0};
            //                const int chunkX = static_cast<int>(tile.position.x) / CHUNK_SIZE;
            //                const int chunkY = static_cast<int>(tile.position.y) / CHUNK_SIZE;
            //                Transform2D key{static_cast<float>(chunkX), static_cast<float>(chunkY)};
            //                tmap->chunks[key].id = "L" + std::to_string(tmap->layer) + "_C" + tmap->id + "[" + std::to_string(key.x) + "," + std::to_string(key.y) + "]";
            //                tmap->chunks[key].tiles.push_back(tile);
            //                tmap->chunks[key].tempData["TEXTURE_NAME"] = tmap->textureName;
            //                tmap->chunks[key].tempData["PAK_ID"] = tmap->pakId;
            //                //LOG_TRACE("Filling chunk {}-{}", key.x, key.y);
            //            }
            //        }
            //    }
            //}
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
