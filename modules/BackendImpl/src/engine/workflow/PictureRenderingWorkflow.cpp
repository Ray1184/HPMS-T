#include "engine/workflow/PictureRenderingWorkflow.h"
#include "engine/workflow/VertexBufferProvider.h"
#include "engine/FrameBufferImpl.h"
#include "engine/resource/TextureImpl.h"
#include "engine/renderable/PictureQuad.h"

#include <SFML/Graphics.hpp>

void hpms::PictureRenderingWorkflow::Render(Window* window, FrameBuffer* framebuffer, Drawable* item)
{
    sf::VertexBuffer* vertexBuffer = hpms::VertexBufferProvider::GetVertexBuffer(item->GetId(), sf::PrimitiveType::TriangleStrip, 4);

    if (item->IsChanged())
    {
        sf::Vertex vertexArray[4];
        auto* pic = dynamic_cast<hpms::PictureQuad*>(item);
        auto* image = pic->GetImage();

        float px = image->position.x;
        float py = image->position.y;

        vertexArray[0].position = sf::Vector2f(px, py);
        vertexArray[1].position = sf::Vector2f(px, py + image->height);
        vertexArray[2].position = sf::Vector2f(px + image->width, py);
        vertexArray[3].position = sf::Vector2f(px + image->width, py + image->height);

        vertexArray[0].texCoords = sf::Vector2f(0, 0);
        vertexArray[1].texCoords = sf::Vector2f(0, image->height);
        vertexArray[2].texCoords = sf::Vector2f(image->width, 0);
        vertexArray[3].texCoords = sf::Vector2f(image->width, image->height);

        vertexBuffer->update(vertexArray);

        item->SetChanged(false);

        LOG_TRACE("VertexBuffer up to date for item {}", item->GetId());

    }

    auto* sfRt = dynamic_cast<hpms::FrameBufferImpl*>(framebuffer)->GetNative();
    auto* sfTexture = dynamic_cast<hpms::TextureImpl*>(item->GetTexture())->GetNative();

    sfRt->draw(*vertexBuffer, sfTexture);
}
