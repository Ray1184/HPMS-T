#pragma once

#include "engine/Renderer.h"
#include "engine/renderable/PictureData.h"
#include "engine/renderable/TilesChunkData.h"

namespace hpms
{
    class RendererImpl : public Renderer
    {
    private:
    public:
        virtual void Render(Window* window, Transform2D& view, std::vector<Drawable*>* drawables) override;
    };
}