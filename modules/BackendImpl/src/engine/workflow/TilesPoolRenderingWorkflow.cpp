#include "engine/workflow/TilesPoolRenderingWorkflow.h"
#include "engine/workflow/TilesPoolRenderingOptimizer.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/WindowImpl.h"
#include "engine/resource/TextureImpl.h"
#include "engine/renderable/TilesPool.h"

#include <SFML/Graphics.hpp>

void hpms::TilesPoolRenderingWorkflow::Render(Window* window, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = VertexBufferProvider::GetVertexBuffer(item->id, sf::PrimitiveType::Triangles);

    if (item->updateVertices || item->forceAll)
    {
        auto* pool = dynamic_cast<TilesPool*>(item);

        auto& tiles = pool->tiles;

        std::vector<sf::Vertex> vertexArray(tiles.size() * 6);
        vertexBuffer->create(tiles.size() * 6);
        unsigned int index = 0;

        for (auto& [position, texCoords]: tiles)
        {
            constexpr float s = TILE_SIZE;
            const float px = position.x * s;
            const float py = position.y * s;
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

        vertexBuffer->update(vertexArray.data());
        LOG_TRACE("VertexBuffer up to date for item {}", item->id);
    }

    auto* sfWin = dynamic_cast<WindowImpl*>(window)->GetNative();
    const auto* sfTexture = dynamic_cast<TextureImpl*>(item->texture)->GetNative();

    sf::RenderStates rs;
    rs.texture = sfTexture;
    rs.blendMode = sf::BlendAlpha;

    sfWin->draw(*vertexBuffer, rs);
}
