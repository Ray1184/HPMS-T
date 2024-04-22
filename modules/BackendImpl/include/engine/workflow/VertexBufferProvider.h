#pragma once

#include "base/Utils.h"

#include <queue>
#include <functional>
#include <ranges>
#include <SFML/Graphics.hpp>

#define MAX_SPRITES_GROUPS_ON_SCREEN 16
#define MAX_TILES_CHUNKS_ON_SCREEN 16
#define MAX_PICTURES_ON_SCREEN 128

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
        VertexBufferCache(): size(0)
        {
        }

        VertexBufferCache(const unsigned int size, const EvictCallback& callback) : size(size), callback(callback)
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

    enum CacheName
    {
        CACHE_TILES_CHUNKS,
        CACHE_SPRITES,
        CACHE_PICTURES
    };


    class VertexBufferProvider
    {
    private:
        static std::unordered_map<CacheName, VertexBufferCache> buffersMap;
        static bool initialized;

    public:
        static void ClearAllBuffers()
        {
            for (auto& snd: buffersMap | std::views::values)
            {
                LOG_DEBUG("Deleting all {} buffers", snd.Size());
                snd.Clear();
            }
        }

        static sf::VertexBuffer* GetVertexBuffer(const CacheName cacheName, const std::string& id, sf::PrimitiveType primitiveType)
        {
            if (!initialized)
            {
                buffersMap[CACHE_TILES_CHUNKS] = VertexBufferCache(MAX_TILES_CHUNKS_ON_SCREEN, [](const std::string& key, sf::VertexBuffer& vb)
                {
                    LOG_TRACE("Deleting buffer {} from CHUNKS cache", key);
                    vb.create(0);
                });
                buffersMap[CACHE_SPRITES] = VertexBufferCache(MAX_SPRITES_GROUPS_ON_SCREEN, [](const std::string& key, sf::VertexBuffer& vb)
                {
                    LOG_TRACE("Deleting buffer {} from SPRITES cache", key);
                    vb.create(0);
                });
                buffersMap[CACHE_PICTURES] = VertexBufferCache(MAX_PICTURES_ON_SCREEN, [](const std::string& key, sf::VertexBuffer& vb)
                {
                    LOG_TRACE("Deleting buffer {} from PICTURES cache", key);
                    vb.create(0);
                });
                initialized = true;
            }
            buffersMap[cacheName].PutIfAbsent(id, sf::VertexBuffer(primitiveType));
            return &(buffersMap[cacheName].Get(id));
        }
    };
}
