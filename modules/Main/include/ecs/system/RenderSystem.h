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
        std::unordered_map<std::string, SpriteData*> allSprites;
        std::vector<SpriteData*> inViewSprites;
        std::unordered_map<std::string, PictureData*> allPictures;
        std::vector<PictureData*> inViewPictures;
        Camera* cam;

        void InitView(const std::vector<Entity*>& entities, RenderSystemParams* args);

        void InitChunks(const std::vector<Entity*>& entities, RenderSystemParams* args);

        void UpdateChunks(const std::vector<Entity*>& entities, RenderSystemParams* args);

        void UpdateDrawables(const std::vector<Entity*>& entities, RenderSystemParams* args);

    public:
        void Init(std::vector<Entity*>& entities, RenderSystemParams* args) override;

        void Update(std::vector<Entity*>& entities, RenderSystemParams* args) override;

        void Cleanup(std::vector<Entity*>& entities, RenderSystemParams* args) override;
    };
}
