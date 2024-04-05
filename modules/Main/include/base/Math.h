#pragma once

namespace hpms
{
    struct AABox
    {
        float x;
        float y;
        float width;
        float height;
    };

    class Math
    {
    public:
        static bool Intersect(const AABox& box, const AABox& view)
        {
            const float boxLeft = box.x;
            const float boxRight = box.x + box.width;
            const float boxTop = box.y;
            const float boxBottom = box.y + box.height;

            const float viewLeft = view.x;
            const float viewRight = view.x + view.width;
            const float viewTop = view.y;
            const float viewBottom = view.y + view.height;

            bool overlapX = (boxLeft < viewRight) && (boxRight > viewLeft);
            bool overlapY = (boxTop < viewBottom) && (boxBottom > viewTop);

            // Restituisce true solo se c'è sovrapposizione in entrambi gli assi
            return overlapX && overlapY;
        }
    };
}
