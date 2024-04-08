#include "engine/workflow/PictureRenderingWorkflow.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/WindowImpl.h"
#include "engine/resource/TextureImpl.h"
#include "engine/renderable/PictureQuad.h"

#include <SFML/Graphics.hpp>

void hpms::PictureRenderingWorkflow::Render(Window* window, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = VertexBufferProvider::GetVertexBuffer(item->GetId(), sf::PrimitiveType::TriangleStrip);

    if (item->IsUpdateVertices() || item->IsForceAll())
    {
        vertexBuffer->create(4);
        sf::Vertex vertexArray[4];
        auto* pic = dynamic_cast<PictureQuad*>(item);
        const auto* image = pic->GetImage();

        const float px = image->position.x;
        const float py = image->position.y;

        vertexArray[0].position = sf::Vector2f(px, py);
        vertexArray[1].position = sf::Vector2f(px, py + image->height);
        vertexArray[2].position = sf::Vector2f(px + image->width, py);
        vertexArray[3].position = sf::Vector2f(px + image->width, py + image->height);

        vertexArray[0].texCoords = sf::Vector2f(0, 0);
        vertexArray[1].texCoords = sf::Vector2f(0, image->height);
        vertexArray[2].texCoords = sf::Vector2f(image->width, 0);
        vertexArray[3].texCoords = sf::Vector2f(image->width, image->height);

        vertexBuffer->update(vertexArray);

        LOG_TRACE("VertexBuffer up to date for item {}", item->GetId());
    }

    auto* sfWin = dynamic_cast<WindowImpl*>(window)->GetNative();
    const auto* sfTexture = dynamic_cast<TextureImpl*>(item->GetTexture())->GetNative();

    sfWin->draw(*vertexBuffer, sfTexture);
}
