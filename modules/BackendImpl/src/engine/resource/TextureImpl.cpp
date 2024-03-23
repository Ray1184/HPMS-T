#include "engine/resource/TextureImpl.h"

sf::Texture* hpms::TextureImpl::GetNative()
{
    return sfmlTexture;
}

unsigned int hpms::TextureImpl::Width()
{
    return sfmlTexture->getSize().x;
}

unsigned int hpms::TextureImpl::Height()
{
    return sfmlTexture->getSize().y;
}

void hpms::TextureImpl::Swap(Texture* other)
{
    auto* sfmlOther = dynamic_cast<TextureImpl*>(other)->GetNative();
    sfmlTexture->swap(*sfmlOther);
}

void hpms::TextureImpl::Allocate(void* ptr, unsigned int size)
{
    sfmlTexture = SAFE_NEW(sf::Texture);
    sfmlTexture->loadFromMemory(ptr, size);
}

void hpms::TextureImpl::Deallocate()
{
    SAFE_DELETE(sf::Texture, sfmlTexture);
}
