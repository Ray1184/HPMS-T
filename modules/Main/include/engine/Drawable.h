#pragma once

#include "base/Defs.h"
#include "engine/resource/Texture.h"

#include <vector>

namespace hpms
{
    enum RenderType
    {
        DRAWABLE_PICTURE,
        DRAWABLE_SIMPLE_SPRITE,
        DRAWABLE_TILES_POOL
    };

    enum RenderStrategy
    {
        STRATEGY_STATIC = 1,
        STRATEGY_UPDATE_VERTICES = 2
    };

    class Drawable
    {
    protected:
        std::string id;
        unsigned int layer;
        Texture* texture;
        bool updateVertices{false};
        bool forceAll{true};

    public:
        virtual ~Drawable() = default;

        virtual RenderType GetType() const = 0;

        [[nodiscard]] unsigned int GetLayer() const
        {
            return layer;
        }

        [[nodiscard]] Texture* GetTexture() const
        {
            return texture;
        }

        [[nodiscard]] bool IsUpdateVertices() const
        {
            return updateVertices;
        }

        [[nodiscard]] bool IsForceAll() const
        {
            return forceAll;
        }

        void SetForceAll(const bool forceAll)
        {
            Drawable::forceAll = forceAll;
        }

        [[nodiscard]] std::string GetId() const
        {
            return id;
        }
    };
}
