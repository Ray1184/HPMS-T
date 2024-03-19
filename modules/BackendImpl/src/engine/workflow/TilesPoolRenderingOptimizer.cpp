#include "engine/workflow/TilesPoolRenderingOptimizer.h"
#include "engine/WindowImpl.h"

#include <unordered_set>

void hpms::TilesPoolRenderingOptimizer::Optimize(Window* window, std::unordered_set<Tile>* in, std::vector<Tile>* out)
{
    const auto& sfWindow = dynamic_cast<hpms::WindowImpl*>(window)->GetNative();
    RemoveOutOfView(window, in, out, sfWindow);
}

void hpms::TilesPoolRenderingOptimizer::RemoveOutOfView(const hpms::Window* window, const std::unordered_set<Tile>* in, std::vector<Tile>* out, sf::RenderWindow* const& sfWindow)
{
    auto& view = sfWindow->getView();
    auto pixelationRatio = window->GetSettings().pixelationRatio;
    for (const auto& tile: *in)
    {
        if (InsideView(tile, view, pixelationRatio))
        {
            out->push_back(tile);
        }
    }
    LOG_TRACE("Keeping {}/{} tiles", out->size(), in->size());
}


bool hpms::TilesPoolRenderingOptimizer::InsideView(const Tile& tile, const sf::View& view, unsigned int ratio)
{

    float tileLeft = tile.screenPosition.x;
    float tileTop = tile.screenPosition.y;
    float tileRight = tileLeft + TILE_SIZE;
    float tileBottom = tileTop + TILE_SIZE;


    sf::FloatRect viewBounds = view.getViewport();
    float viewLeft = (view.getCenter().x - (viewBounds.width / 2) * view.getSize().x) / ratio;
    float viewRight = (view.getCenter().x + (viewBounds.width / 2) * view.getSize().x) / ratio;
    float viewTop = (view.getCenter().y - (viewBounds.height / 2) * view.getSize().y) / ratio;
    float viewBottom = (view.getCenter().y + (viewBounds.height / 2) * view.getSize().y) / ratio;

    return (tileRight >= viewLeft && tileLeft <= viewRight &&
            tileBottom >= viewTop && tileTop <= viewBottom);

}
