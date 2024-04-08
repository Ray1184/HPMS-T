// #include "engine/workflow/TilesPoolRenderingOptimizer.h"
// #include "engine/WindowImpl.h"
//
// #include <unordered_set>
//
// void hpms::TilesPoolRenderingOptimizer::Optimize(Window* window, const std::unordered_set<Tile>* in, std::vector<Tile>* out)
// {
//     const auto& sfWindow = dynamic_cast<WindowImpl*>(window)->GetNative();
//     RemoveOutOfView(window, in, out, sfWindow);
// }
//
// void hpms::TilesPoolRenderingOptimizer::RemoveOutOfView(const Window* window, const std::unordered_set<Tile>* in, std::vector<Tile>* out, sf::RenderWindow* const& sfWindow)
// {
//     auto& view = sfWindow->getView();
//     const auto pixelationRatio = window->GetSettings().pixelationRatio;
//     for (const auto& tile: *in)
//     {
//         if (InsideView(tile, view, pixelationRatio))
//         {
//             out->push_back(tile);
//         }
//     }
//     LOG_TRACE("Keeping {}/{} tiles", out->size(), in->size());
// }
//
//
// bool hpms::TilesPoolRenderingOptimizer::InsideView(const Tile& tile, const sf::View& view, const unsigned int ratio)
// {
//     const float tileLeft = tile.position.x;
//     const float tileTop = tile.position.y;
//     const float tileRight = tileLeft + TILE_SIZE;
//     const float tileBottom = tileTop + TILE_SIZE;
//
//
//     const sf::FloatRect viewBounds = view.getViewport();
//     const float viewLeft = (view.getCenter().x - viewBounds.width / 2 * view.getSize().x) / static_cast<float>(ratio);
//     const float viewRight = (view.getCenter().x + viewBounds.width / 2 * view.getSize().x) / static_cast<float>(ratio);
//     const float viewTop = (view.getCenter().y - viewBounds.height / 2 * view.getSize().y) / static_cast<float>(ratio);
//     const float viewBottom = (view.getCenter().y + viewBounds.height / 2 * view.getSize().y) / static_cast<float>(ratio);
//
//     return tileRight >= viewLeft && tileLeft <= viewRight &&
//            tileBottom >= viewTop && tileTop <= viewBottom;
// }
