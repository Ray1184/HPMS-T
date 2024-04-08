#include "engine/RendererImpl.h"
#include "engine/RenderingWorkflowFactory.h"
#include "engine/WindowImpl.h"

#include <algorithm>

void hpms::RendererImpl::Render(Window* window, Transform2D& view, std::vector<Drawable*>* drawables)
{
    auto* sfWindow = dynamic_cast<WindowImpl*>(window)->GetNative();
    sf::View sfView = sfWindow->getView();
    const auto oldX = sfView.getSize().x / 2;
    const auto oldY = sfView.getSize().y / 2;
    sfView.setCenter(oldX + view.x, oldY + view.y);
    sfWindow->setView(sfView);
    sfWindow->clear(sf::Color::Black);
    auto sortingByLayerPredicate = [](const Drawable* a, const Drawable* b)
    {
        return a->layer < b->layer;
    };
    std::ranges::sort(*drawables, sortingByLayerPredicate);

    for (auto* item: *drawables)
    {
        auto* workflow = RenderingWorkflowFactory::GetRenderingWorkflow(item->GetType());
        workflow->Render(window, item);
        item->forceAll = false;
    }

    sfWindow->display();
}
