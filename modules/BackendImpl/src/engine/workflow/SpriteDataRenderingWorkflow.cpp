#include "engine/workflow/SpriteDataRenderingWorkflow.h"

#include <engine/renderable/SpriteData.h>

#include "engine/workflow/VertexBufferProvider.h"
#include "engine/WindowImpl.h"
#include "engine/resource/TextureImpl.h"

#include <SFML/Graphics.hpp>

void hpms::SpriteDataRenderingWorkflow::Render(Window* window, Drawable* item)
{
    auto* compSprite = dynamic_cast<SpriteBatch*>(item);
    std::unordered_map<std::string, sf::VertexBuffer*> vertexBuffers;
    vertexBuffers[compSprite->id] = VertexBufferProvider::GetVertexBuffer(CACHE_SPRITES, compSprite->id, sf::PrimitiveType::Triangles);

    auto sortingByDepthPredicate = [](const SpriteData* a, const SpriteData* b)
    {
        const float depthA = a->position.y + static_cast<float>(a->height);
        const float depthB = b->position.y + static_cast<float>(b->height);
        return depthA < depthB;
    };
    std::ranges::sort(compSprite->subSprites, sortingByDepthPredicate);

    bool createVb = false;
    unsigned long vertexCount = 0;
    for (const auto* subSprite: compSprite->subSprites)
    {
        if (subSprite->updateVertices || subSprite->forceAll)
        {
            vertexCount += subSprite->tiles.size();
            createVb = true;
        }
    }
    if (createVb)
    {
        vertexCount *= 6;
        std::vector<sf::Vertex> vertexArray(vertexCount);
        vertexBuffers[compSprite->id]->create(vertexCount);
        int index = 0;
        for (auto* subSprite : compSprite->subSprites)
        {
            auto& tiles = subSprite->tiles;
            const float spritePosX = subSprite->position.x;
            const float spritePosY = subSprite->position.y;
            subSprite->forceAll = false;

            for (auto& [position, texCoords]: tiles)
            {
                constexpr float s = TILE_SIZE;
                const float px = position.x * s + spritePosX;
                const float py = position.y * s + spritePosY;
                const float tx = texCoords.x * s;
                const float ty = texCoords.y * s;

                vertexArray[index + 0].position = sf::Vector2f(px, py);
                vertexArray[index + 1].position = sf::Vector2f(px, py + s);
                vertexArray[index + 2].position = sf::Vector2f(px + s, py);
                vertexArray[index + 3].position = sf::Vector2f(px + s, py);
                vertexArray[index + 4].position = sf::Vector2f(px, py + s);
                vertexArray[index + 5].position = sf::Vector2f(px + s, py + s);

                vertexArray[index + 0].texCoords = sf::Vector2f(tx, ty);
                vertexArray[index + 1].texCoords = sf::Vector2f(tx, ty + s);
                vertexArray[index + 2].texCoords = sf::Vector2f(tx + s, ty);
                vertexArray[index + 3].texCoords = sf::Vector2f(tx + s, ty);
                vertexArray[index + 4].texCoords = sf::Vector2f(tx, ty + s);
                vertexArray[index + 5].texCoords = sf::Vector2f(tx + s, ty + s);

                index += 6;
            }
        }
        vertexBuffers[compSprite->id]->update(vertexArray.data());
        LOG_TRACE("VertexBuffer up to date for sub sprite batch {}", compSprite->id);
    }



    auto* sfWin = dynamic_cast<WindowImpl*>(window)->GetNative();
    auto* texture = compSprite->subSprites.at(0)->texture;
    const auto* sfTexture = dynamic_cast<TextureImpl*>(texture)->GetNative();
    sfWin->draw(*(vertexBuffers[compSprite->id]), sfTexture);
}
