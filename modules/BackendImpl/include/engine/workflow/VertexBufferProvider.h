#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace hpms
{
    class VertexBufferProvider
    {
    private:
        static std::unordered_map<std::string, sf::VertexBuffer> buffers;

    public:
        static void ClearAllBuffers()
        {
            for (const auto& item: buffers)
            {
                buffers[item.first].create(0);
            }
            buffers.clear();
        }

        static sf::VertexBuffer* GetVertexBuffer(const std::string& id, sf::PrimitiveType primitiveType, unsigned long long vertices)
        {
            if (!buffers.contains(id))
            {
                buffers[id] = sf::VertexBuffer(primitiveType);
                buffers[id].create(vertices);
            }
            return &(buffers[id]);
        }
    };
}
