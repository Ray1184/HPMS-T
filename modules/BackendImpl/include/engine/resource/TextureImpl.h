#pragma once

#include "engine/resource/Texture.h"
#include "engine/NativeData.h"

#include <SFML/Graphics/Texture.hpp>

namespace hpms
{
    class TextureImpl : public Texture, public NativeData<sf::Texture>
    {
    private:
        sf::Texture* sfmlTexture{nullptr};
        std::string resId;

    public:
        explicit TextureImpl(const std::string& resId);

        sf::Texture* GetNative() override;

        unsigned int Width() override;

        unsigned int Height() override;

        void Swap(Texture* other) override;

        std::string ResourceId() override;

    protected:
        void Allocate(void* ptr, unsigned int size) override;

        void Deallocate() override;
    };
}
