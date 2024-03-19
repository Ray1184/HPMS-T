#pragma once

#include "engine/FrameBuffer.h"
#include "engine/NativeData.h"
#include "base/Utils.h"

#include <SFML/Graphics.hpp>

namespace hpms
{

    class FrameBufferImpl : public hpms::FrameBuffer, hpms::NativeData<sf::RenderTexture>
    {
    private:
        sf::RenderTexture* sfmlFrameBuffer;
        unsigned int width;
        unsigned int height;
    public:
        explicit FrameBufferImpl(unsigned int width, unsigned int height);

        virtual ~FrameBufferImpl();

        sf::RenderTexture* GetNative() override;

        [[nodiscard]] inline unsigned int GetWidth() const override
        {
            return width;
        }

        [[nodiscard]] inline unsigned int GetHeight() const override
        {
            return height;
        }


    };
}