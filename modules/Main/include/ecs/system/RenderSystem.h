#pragma once

#include "ecs/System.h"
#include "ecs/component/Components.h"
#include "engine/renderable/TilesChunkData.h"
#include "engine/renderable/PictureData.h"
#include "engine/renderable/SpriteData.h"
#include "engine/Renderer.h"
#include "engine/Window.h"

#include <vector>
#include <unordered_map>

namespace hpms
{
    struct RenderSystemParams
    {
        Renderer* renderer;
        Window* window;
    };

    class RenderSystem : public System<RenderSystemParams>
    {
    private:
        std::unordered_map<unsigned int, TilesMap*> allChunks;
        std::vector<TilesChunkData*> inViewChunks;
        std::unordered_map<unsigned int, std::vector<Sprite*>> allSprites;
        std::vector<SpriteData*> inViewSprites;
        std::unordered_map<unsigned int, Picture*> allPictures;
        std::vector<PictureData*> inViewPictures;
        Camera* cam{nullptr};

        void InitView(const std::vector<Entity*>& entities);

        void InitChunks(const std::vector<Entity*>& entities);

        void InitSprites(const std::vector<Entity*>& entities);

        void InitPictures(const std::vector<Entity*>& entities);

        void UpdateChunks();

        void UpdateSprites();

        void UpdatePictures();

        static void UpdatePositions(const std::vector<Entity*>& entities);

        static void FindNearestFaces(const Transform2D& view, Transform2D(& faces)[9]);

    public:
        void Init(std::vector<Entity*>& entities, RenderSystemParams* args) override;

        void Update(std::vector<Entity*>& entities, RenderSystemParams* args) override;

        void Cleanup(std::vector<Entity*>& entities, RenderSystemParams* args) override;
    };
}
