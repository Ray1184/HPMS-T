#include "engine/workflow/TilesPoolRenderingWorkflow.h"
#include "engine/workflow/TilesPoolRenderingOptimizer.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/FrameBufferImpl.h"
#include "engine/resource/TextureImpl.h"
#include "engine/renderable/TilesPool.h"

#include <SFML/Graphics.hpp>

void hpms::TilesPoolRenderingWorkflow::Render(Window* window, FrameBuffer* framebuffer, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = VertexBufferProvider::GetVertexBuffer(item->GetId(), sf::PrimitiveType::Triangles, 0);

    if (item->IsChanged())
    {

        auto* tiles = dynamic_cast<TilesPool*>(item);

        std::vector<Tile> optimizedTiles;
        TilesPoolRenderingOptimizer::Optimize(window, tiles->GetTiles(), &optimizedTiles);
        std::ranges::sort(optimizedTiles);

        std::vector<sf::Vertex> vertexArray(optimizedTiles.size() * 6);
        vertexBuffer->create(optimizedTiles.size() * 6);
        unsigned int index = 0;

        for (auto& [position, texCoords, depth]: optimizedTiles)
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
        item->SetChanged(false);

        LOG_TRACE("VertexBuffer up to date for item {}", item->GetId());
    }
    auto* sfRt = dynamic_cast<FrameBufferImpl*>(framebuffer)->GetNative();
    const auto* sfTexture = dynamic_cast<TextureImpl*>(item->GetTexture())->GetNative();

    sf::RenderStates rs;
    rs.texture = sfTexture;
    rs.blendMode = sf::BlendAlpha;

    sfRt->draw(*vertexBuffer, rs);
}

