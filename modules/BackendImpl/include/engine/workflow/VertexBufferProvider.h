#pragma once

#include "base/Utils.h"

#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

#define VERTEX_BUFFER_CACHE_SIZE 16

namespace hpms
{
    typedef std::function<void(const std::string&, sf::VertexBuffer&)> EvictCallback;

    class VertexBufferCache
    {
    private:
        std::unordered_map<std::string, sf::VertexBuffer> cache;
        std::queue<std::string> fifo;
        unsigned int size;
        EvictCallback callback;

    public:
        explicit VertexBufferCache(const unsigned int size, const EvictCallback& callback) : size(size), callback(callback)
        {
        }

        [[nodiscard]] unsigned int Size() const
        {
            return cache.size();
        }

        void PutIfAbsent(const std::string& key, const sf::VertexBuffer& vb)
        {
            if (cache.contains(key))
            {
                return;
            }
            if (fifo.size() >= size)
            {
                const auto& oldestKey = fifo.front();
                auto& evicted = cache[oldestKey];
                callback(oldestKey, evicted);
                cache.erase(oldestKey);
                fifo.pop();
            }
            fifo.push(key);
            cache[key] = vb;
        }

        sf::VertexBuffer& Get(const std::string& key)
        {
            if (!cache.contains(key))
            {
                LOG_ERROR("VertexBuffer {} not present inside cache", key);
                RUNTIME_EXCEPTION("VertexBuffer {} not present inside cache", key);
            }
            return cache[key];
        }

        void Clear()
        {
            std::queue<std::string> empty;
            std::swap(fifo, empty);
            for (auto& [fst, snd]: cache)
            {
                auto& vb = snd;
                callback(fst, vb);
            }
            cache.clear();
        }
    };


    class VertexBufferProvider
    {
    private:
        static VertexBufferCache buffers;

    public:
        static void ClearAllBuffers()
        {
            LOG_DEBUG("Deleting all {} buffers", buffers.Size());
            buffers.Clear();
        }

        static sf::VertexBuffer* GetVertexBuffer(const std::string& id, sf::PrimitiveType primitiveType)
        {
            buffers.PutIfAbsent(id, sf::VertexBuffer(primitiveType));
            return &(buffers.Get(id));
        }
    };
}
