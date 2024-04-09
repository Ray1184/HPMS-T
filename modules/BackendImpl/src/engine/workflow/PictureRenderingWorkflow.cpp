#include "engine/workflow/PictureRenderingWorkflow.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/WindowImpl.h"
#include "engine/resource/TextureImpl.h"
#include "engine/renderable/PictureData.h"

#include <SFML/Graphics.hpp>

void hpms::PictureRenderingWorkflow::Render(Window* window, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = VertexBufferProvider::GetVertexBuffer(item->id, sf::PrimitiveType::TriangleStrip);

    if (item->updateVertices || item->forceAll)
    {
        vertexBuffer->create(4);
        sf::Vertex vertexArray[4];
        auto* pic = dynamic_cast<PictureData*>(item);
        const float px = pic->image.position.x;
        const float py = pic->image.position.y;

        vertexArray[0].position = sf::Vector2f(px, py);
        vertexArray[1].position = sf::Vector2f(px, py + pic->image.height);
        vertexArray[2].position = sf::Vector2f(px + pic->image.width, py);
        vertexArray[3].position = sf::Vector2f(px + pic->image.width, py + pic->image.height);

        vertexArray[0].texCoords = sf::Vector2f(0, 0);
        vertexArray[1].texCoords = sf::Vector2f(0, pic->image.height);
        vertexArray[2].texCoords = sf::Vector2f(pic->image.width, 0);
        vertexArray[3].texCoords = sf::Vector2f(pic->image.width, pic->image.height);

        vertexBuffer->update(vertexArray);

        LOG_TRACE("VertexBuffer up to date for item {}", item->id);
    }

    auto* sfWin = dynamic_cast<WindowImpl*>(window)->GetNative();
    const auto* sfTexture = dynamic_cast<TextureImpl*>(item->texture)->GetNative();

    sfWin->draw(*vertexBuffer, sfTexture);
}
