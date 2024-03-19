#include "ecs/system/RenderSystem.h"
#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/TilesPool.h"
#include "base/ResourcesHandler.h"

void hpms::RenderSystem::Update(std::vector<Entity*>& entities, Renderer* renderer, Window* window, FrameBuffer* framebuffer)
{
    std::vector<Drawable*> drawables;
    for (auto* entity: entities)
    {
        Transform2D transform2D;
        if (entity->HasComponent(ComponentType::COMPONENT_MOVABLE))
        {
            auto* mov = entity->GetComponent<Movable>(ComponentType::COMPONENT_MOVABLE);
            transform2D = mov->position;
        }
        if (entity->HasComponent(ComponentType::COMPONENT_GRAPHICS))
        {
            auto* g = entity->GetComponent<Picture>(ComponentType::COMPONENT_GRAPHICS);
            auto* texture = hpms::ResourcesHandler::Provide<hpms::Texture>(g->pakId, g->textureName);

            if (auto* pic = dynamic_cast<Picture*>(g))
            {
                auto drawable = hpms::PictureQuad(pic->layer, texture, transform2D);
                drawable.SetChanged(entity->IsChanged());
                drawables.push_back(&drawable);
            }
        }
        entity->SetChanged(false);
    }
    renderer->Render(window, framebuffer, &drawables);
}

