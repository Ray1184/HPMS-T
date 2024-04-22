#include "engine/workflow/VertexBufferProvider.h"

std::unordered_map<hpms::CacheName, hpms::VertexBufferCache> hpms::VertexBufferProvider::buffersMap = std::unordered_map<CacheName, VertexBufferCache>();
bool hpms::VertexBufferProvider::initialized = false;
