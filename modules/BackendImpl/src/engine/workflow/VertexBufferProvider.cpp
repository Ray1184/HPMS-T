#include "engine/workflow/VertexBufferProvider.h"

hpms::VertexBufferCache hpms::VertexBufferProvider::buffers = VertexBufferCache(VERTEX_BUFFER_CACHE_SIZE, [](const std::string& key, sf::VertexBuffer& vb)
{
    LOG_TRACE("Deleting buffer {} from cache", key);
    vb.create(0);
});
