#include "engine/FrameBufferImpl.h"

hpms::FrameBufferImpl::FrameBufferImpl(unsigned int width, unsigned int height): width(width), height(height)
{
    sfmlFrameBuffer = SAFE_NEW(sf::RenderTexture);
    if (!sfmlFrameBuffer->create(width, height))
    {
        LOG_ERROR("Error creating frame buffer");
        RUNTIME_EXCEPTION("Error creating frame buffer");
    }
}


sf::RenderTexture* hpms::FrameBufferImpl::GetNative()
{
    return sfmlFrameBuffer;
}


hpms::FrameBufferImpl::~FrameBufferImpl()
{
    SAFE_DELETE(sf::RenderTexture, sfmlFrameBuffer);
}
