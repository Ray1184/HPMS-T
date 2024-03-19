#pragma once

#include "engine/GameLogic.h"
#include "engine/renderable/PictureQuad.h"
#include "base/Utils.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "ecs/component/Components.h"
#include "ecs/system/Systems.h"
#include "ecs/Entity.h"

#include <random>


namespace hpms
{
    class TestLogic : public hpms::GameLogic
    {
    private:
        hpms::ResourceSupplierImpl* resSupplier;
        std::vector<hpms::Entity*> entities;

    public:
        [[noreturn]] inline virtual void Init() override
        {

            hpms::Logs::logLevel = hpms::LogLevel::TRACE;
            resSupplier = SAFE_NEW(hpms::ResourceSupplierImpl);
            hpms::ResourcesHandler::PreloadResources("pak1.zip", resSupplier);
            auto* backTex = hpms::ResourcesHandler::Provide<hpms::Texture>("pak1.zip", "/textures/background.png");
            auto* tilemapTex = hpms::ResourcesHandler::Provide<hpms::Texture>("pak1.zip", "/textures/tileset_custom_48_48.png");
            auto* pic = SAFE_NEW(hpms::PictureQuad, 0, backTex, hpms::Transform2D{0, 0});
            Entity* picEntity = SAFE_NEW(hpms::Entity);
            auto* compPic = SAFE_NEW(hpms::Picture);
            compPic->textureName = "/textures/background.png";
            compPic->pakId = "pak1.zip";
            compPic->layer = 0;
            picEntity->AddComponent(compPic);
            //auto* chunk1 = SAFE_NEW(hpms::TilesPool, 1, tilemapTex);
            //auto* chunk2 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk3 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk4 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk5 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk6 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk7 = SAFE_NEW(hpms::TilesPool);
            //auto* chunk8 = SAFE_NEW(hpms::TilesPool);

            //FillChunkRandom(chunk1, 8);
            //FillChunkRandom(chunk2, 1);
            //FillChunkRandom(chunk3, 1);
            //FillChunkRandom(chunk4, 1);
            //FillChunkRandom(chunk5, 1);
            //FillChunkRandom(chunk6, 1);
            //FillChunkRandom(chunk7, 1);
            //FillChunkRandom(chunk8, 1);

            entities.push_back(picEntity);
            //drawables.push_back(chunk1);
            //drawables.push_back(chunk2);
            //drawables.push_back(chunk3);
            //drawables.push_back(chunk4);
            //drawables.push_back(chunk5);
            //drawables.push_back(chunk6);
            //drawables.push_back(chunk7);
            //drawables.push_back(chunk8);
        }

        void FillChunkRandom(TilesPool* chunk, int iter) const
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            // Definisci la distribuzione per generare numeri tra 0 e 2 (inclusi)
            std::uniform_int_distribution<int> distribution(-1, 5);

            for (int n = 0; n < iter; n++)
            {
                for (int x = 0; x < 20; x++)
                {
                    for (int y = 0; y < 15; y++)
                    {
                        //for (int z = -8; z < 8; z++)
                        {
                            int randomX = 1;//distribution(gen);
                            int randomY = 1;//distribution(gen);
                            int randomZ = 1;//distribution(gen);
                            Tile t{(float) x * randomX, (float) y * randomY, 0, 0, 0};
                            chunk->AddTile(t);
                        }
                    }
                }
            }
        }

        inline virtual void HandleInput(hpms::InputHandler* inputHandler) override
        {

        }

        inline virtual void Update(float tpf) override
        {
        }

        inline virtual void Render(Renderer* renderer, Window* window, FrameBuffer* framebuffer) override
        {
            RenderSystem::Update(entities, renderer, window, framebuffer);
            //renderer->Render(window, framebuffer, &drawables);
        }

        inline virtual void Cleanup() override
        {
            hpms::VertexBufferProvider::ClearAllBuffers();
            for (auto* item: entities)
            {
                SAFE_DELETE(hpms::Entity, item);
            }

            hpms::ResourcesHandler::UnloadResources("pak1.zip", resSupplier);
            SAFE_DELETE(hpms::ResourceSupplierImpl, resSupplier);
        }
    };
}