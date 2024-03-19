#pragma once

#include "engine/resource/Texture.h"
#include "engine/NativeData.h"

#include <SFML/Graphics/Texture.hpp>

namespace hpms
{
    class TextureImpl : public hpms::Texture, public hpms::NativeData<sf::Texture>
    {
    private:
        sf::Texture* sfmlTexture;
    public:
        sf::Texture* GetNative() override;

        unsigned int Width() override;

        unsigned int Height() override;

        void Swap(Texture* other) override;

    protected:
        void Allocate(void* ptr, unsigned int size) override;

        void Deallocate() override;
    };
}