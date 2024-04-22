#include "engine/workflow/PictureDataRenderingWorkflow.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/renderable/PictureData.h"
#include "engine/WindowImpl.h"
#include "engine/resource/TextureImpl.h"

#include <SFML/Graphics.hpp>

void hpms::PictureDataRenderingWorkflow::Render(Window* window, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = VertexBufferProvider::GetVertexBuffer(CACHE_PICTURES, item->id, sf::PrimitiveType::TriangleStrip);

    if (item->updateVertices || item->forceAll)
    {
        vertexBuffer->create(4);
        sf::Vertex vertexArray[4];
        auto* pic = dynamic_cast<PictureData*>(item);
        const float px = pic->position.x;
        const float py = pic->position.y;

        vertexArray[0].position = sf::Vector2f(px, py);
        vertexArray[1].position = sf::Vector2f(px, py + pic->height);
        vertexArray[2].position = sf::Vector2f(px + pic->width, py);
        vertexArray[3].position = sf::Vector2f(px + pic->width, py + pic->height);

        vertexArray[0].texCoords = sf::Vector2f(0, 0);
        vertexArray[1].texCoords = sf::Vector2f(0, pic->height);
        vertexArray[2].texCoords = sf::Vector2f(pic->width, 0);
        vertexArray[3].texCoords = sf::Vector2f(pic->width, pic->height);

        vertexBuffer->update(vertexArray);

        LOG_TRACE("VertexBuffer up to date for picture {}", item->id);
    }

    auto* sfWin = dynamic_cast<WindowImpl*>(window)->GetNative();
    const auto* sfTexture = dynamic_cast<TextureImpl*>(item->texture)->GetNative();

    sfWin->draw(*vertexBuffer, sfTexture);
}
