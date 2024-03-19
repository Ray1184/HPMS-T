#include "engine/workflow/TilesPoolRenderingWorkflow.h"
#include "engine/workflow/TilesPoolRenderingOptimizer.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/FrameBufferImpl.h"
#include "engine/resource/TextureImpl.h"
#include "engine/renderable/TilesPool.h"

#include <SFML/Graphics.hpp>

void hpms::TilesPoolRenderingWorkflow::Render(Window* window, FrameBuffer* framebuffer, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = hpms::VertexBufferProvider::GetVertexBuffer(item->GetId(), sf::PrimitiveType::Triangles, 0);

    if (item->IsChanged())
    {

        auto* tiles = dynamic_cast<hpms::TilesPool*>(item);

        std::vector<Tile> optimizedTiles;
        hpms::TilesPoolRenderingOptimizer::Optimize(window, tiles->GetTiles(), &optimizedTiles);
        std::sort(optimizedTiles.begin(), optimizedTiles.end());

        std::vector<sf::Vertex> vertexArray(optimizedTiles.size() * 6);
        vertexBuffer->create(optimizedTiles.size() * 6);
        unsigned int index = 0;

        for (auto& tile: optimizedTiles)
        {
            float s = TILE_SIZE;
            float px = tile.position.x * s;
            float py = tile.position.y * s;
            float tx = tile.texCoords.x * s;
            float ty = tile.texCoords.y * s;

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
    auto* sfRt = dynamic_cast<hpms::FrameBufferImpl*>(framebuffer)->GetNative();
    auto* sfTexture = dynamic_cast<hpms::TextureImpl*>(item->GetTexture())->GetNative();

    sf::RenderStates rs;
    rs.texture = sfTexture;
    rs.blendMode = sf::BlendAlpha;

    sfRt->draw(*vertexBuffer, rs);
}

