#pragma once

#include "ecs/System.h"
#include "ecs/component/Components.h"
#include "engine/renderable/TilesPool.h"
#include "engine/renderable/PictureQuad.h"
#include "engine/Renderer.h"
#include "engine/FrameBuffer.h"
#include "engine/Window.h"

#include <vector>
#include <unordered_map>

namespace hpms
{
    struct RenderSystemParams
    {
        Renderer* renderer;
        Window* window;
        FrameBuffer* frameBuffer;
    };

    class RenderSystem : public System<RenderSystemParams>
    {
    private:
        std::unordered_map<unsigned int, TilesPool*> poolsCache;

        std::unordered_map<unsigned int, PictureQuad*> picturesCache;

        std::unordered_set<unsigned int> layersToUpdate;

        void UpdateDrawables(const std::unordered_map<std::string, Movable*>& transforms, const std::vector<std::pair<std::string, Picture*>>& pictures, const std::vector<std::pair<std::string, Sprite*>>& sprites);

        static std::string CreateMergedId(const std::vector<std::pair<std::string, Sprite*>>& sprites);

        static Texture* MergeTextures(const std::vector<std::pair<std::string, Sprite*>>& sprites);

    public:
        void Init(std::vector<Entity*>& entities, RenderSystemParams* args) override;

        void Update(std::vector<Entity*>& entities, RenderSystemParams* args) override;

        void Cleanup(std::vector<Entity*>& entities, RenderSystemParams* args) override;
    };
}