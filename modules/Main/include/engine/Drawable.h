#pragma once

#include "engine/resource/Texture.h"

#include <unordered_map>
#include <utility>
#include <string>

namespace hpms
{
    enum RenderType
    {
        DRAWABLE_PICTURE,
        DRAWABLE_SPRITE,
        DRAWABLE_TILES_CHUNK_DATA
    };

    struct Drawable
    {
        std::string id{"_NONE"};
        unsigned int layer{0};
        Texture* texture{nullptr};
        bool updateVertices{false};
        bool forceAll{true};
        std::unordered_map<std::string, std::string> customStrings;
        bool visible{true};

        Drawable() = default;

        Drawable(std::string id, const unsigned int layer, Texture* texture, const bool updateVertices)
            : id(std::move(id)),
              layer(layer),
              texture(texture),
              updateVertices(updateVertices)
        {
        }

        virtual ~Drawable() = default;

        [[nodiscard]] virtual RenderType GetType() const = 0;
    };
}
