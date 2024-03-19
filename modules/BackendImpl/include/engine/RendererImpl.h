#pragma once

#include "engine/Renderer.h"
#include "engine/renderable/PictureQuad.h"
#include "engine/renderable/TilesPool.h"

namespace hpms
{
    class RendererImpl : public Renderer
    {
    private:
    public:
        virtual void Render(hpms::Window* window, hpms::FrameBuffer* framebuffer, std::vector<hpms::Drawable*>* drawables) override;
    };
}