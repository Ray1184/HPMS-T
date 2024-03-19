#include "ecs/system/RenderSystem.h"
#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/TilesPool.h"
#include "base/ResourcesHandler.h"

void hpms::RenderSystem::Update(std::vector<Entity*>& entities, Renderer* renderer, Window* window, FrameBuffer* framebuffer)
{
    std::vector<Drawable*> drawables;
    for (auto* entity: entities)
    {
        Verify(entity);
        Transform3D transform3D;
        if (entity->HasComponent(ComponentType::COMPONENT_MOVABLE))
        {
            auto* mov = entity->GetComponent<Movable>(ComponentType::COMPONENT_MOVABLE);
            transform3D = mov->position;
        }
        if (entity->HasComponent(ComponentType::COMPONENT_PICTURE))
        {
            auto* pic = entity->GetComponent<Picture>(ComponentType::COMPONENT_PICTURE);
            auto* texture = hpms::ResourcesHandler::Provide<hpms::Texture>(pic->pakId, pic->textureName);
            auto drawable = hpms::PictureQuad(pic->layer, texture, transform3D.transform2D);
            drawable.SetChanged(entity->IsChanged());
            drawables.push_back(&drawable);
        }
        entity->SetChanged(false);
    }
    renderer->Render(window, framebuffer, &drawables);
}

void hpms::RenderSystem::Verify(hpms::Entity* entity)
{
    if (entity->HasComponent(ComponentType::COMPONENT_SPRITE) && entity->HasComponent(ComponentType::COMPONENT_PICTURE))
    {
        LOG_ERROR("An entity cannot have a SPRITE and a PICTURE component at the same time");
        RUNTIME_EXCEPTION("An entity cannot have a SPRITE and a PICTURE component at the same time");
    }
}
