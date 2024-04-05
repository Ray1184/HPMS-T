#pragma once

#include "ecs/System.h"
#include "ecs/component/Components.h"
#include "engine/renderable/TilesPool.h"
#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/SimpleSprite.h"
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
        std::unordered_map<Transform2D, TilesPool*> allChunks;

        std::vector<TilesPool*> inViewChunks;

        std::unordered_map<std::string, SimpleSprite*> allSprites;

        std::vector<SimpleSprite*> inViewSprites;

        std::unordered_map<std::string, PictureQuad*> allPictures;

        std::vector<PictureQuad*> inViewPictures;

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
