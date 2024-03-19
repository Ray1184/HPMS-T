#include "engine/RendererImpl.h"
#include "engine/RenderingWorkflowFactory.h"
#include "engine/WindowImpl.h"
#include "engine/FrameBufferImpl.h"

#include <algorithm>

void hpms::RendererImpl::Render(hpms::Window* window, hpms::FrameBuffer* framebuffer,
                                std::vector<hpms::Drawable*>* drawables)
{
    auto* sfWindow = dynamic_cast<hpms::WindowImpl*>(window)->GetNative();
    auto* sfRt = dynamic_cast<hpms::FrameBufferImpl*>(framebuffer)->GetNative();

    sfRt->clear(sf::Color::Black);
    auto sortingByLayerPredicate = [](hpms::Drawable* a, hpms::Drawable* b)
    {
        return a->GetLayer() < b->GetLayer();
    };
    std::sort(drawables->begin(), drawables->end(), sortingByLayerPredicate);

    for (auto* item: *drawables)
    {
        auto* workflow = hpms::RenderingWorkflowFactory::GetRenderingWorkflow(item->GetType());
        workflow->Render(window, framebuffer, item);
    }
    sfRt->display();
    sfWindow->clear();
    sf::Sprite texture(sfRt->getTexture());
    texture.scale(window->GetSettings().pixelationRatio, window->GetSettings().pixelationRatio);
    sfWindow->draw(texture);
    sfWindow->display();

}

