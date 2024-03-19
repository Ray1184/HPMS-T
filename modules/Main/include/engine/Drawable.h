#pragma once

#include "base/Defs.h"
#include "engine/resource/Texture.h"

#include <vector>

namespace hpms
{
    enum RenderType
    {
        DRAWABLE_PICTURE,
        DRAWABLE_TILES_POOL
    };

    class Drawable
    {
    protected:
        unsigned int layer;
        hpms::Texture* texture;
        bool changed{true};
    public:
        inline virtual ~Drawable() = default;

        virtual RenderType GetType() const = 0;

        virtual const std::string GetId() const = 0;

        [[nodiscard]] inline unsigned int GetLayer() const
        {
            return layer;
        }

        [[nodiscard]] inline Texture* GetTexture() const
        {
            return texture;
        }

        [[nodiscard]] inline bool IsChanged() const
        {
            return changed;
        }

        inline void SetChanged(bool changed)
        {
            Drawable::changed = changed;
        }
    };
}