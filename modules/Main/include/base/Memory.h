#pragma once

#include "base/AppError.h"
#include "thirdparty/VariadicTable.h"

#include <unordered_map>
#include <string>
#include <sstream>
#include <typeinfo>

#define SAFE_NEW(T, ...) hpms::Memory::SafeNew<T>(__VA_ARGS__)
#define SAFE_NEW_ARRAY(T, size) hpms::Memory::SafeNewArray<T>(size)

#define SAFE_DELETE(T, ptr) hpms::Memory::SafeDelete<T>(ptr)
#define SAFE_DELETE_ARRAY(T, ptr) hpms::Memory::SafeDeleteArray<T>(ptr)

#define MEMORY_DUMP hpms::Memory::MemoryDump();

namespace hpms
{
    class Memory
    {
    private:
        inline static std::unordered_map<std::string, int> allocMap;

    public:

        inline static std::stringstream MemoryDump()
        {

            VariadicTable<std::string, int> vt({"OBJECT", "PENDING ALLOCATIONS"});
            std::stringstream dump;
            dump << "### MEMORY DUMP REPORT ###" << std::endl << std::endl;
            int leaks = 0;
            for (const auto& pair: allocMap)
            {
                vt.addRow(pair.first, pair.second);
                leaks += pair.second;
            }
            vt.setTotal("TOTAL", leaks);

            if (leaks == 0)
            {
                dump << "OK, no potential memory leaks detected!" << std::endl;
            } else if (leaks > 0)
            {
                dump << "ERROR, potential memory leaks detected! " << leaks << " allocations not set free."
                     << std::endl;
            } else
            {
                dump << "WARNING, unnecessary memory dealloc detected! " << -leaks << " useless de-allocations."
                     << std::endl;
            }
            dump << "See details below..." << std::endl << std::endl;
            vt.print(dump);
            return dump;
        }


        template<typename T, typename... ARGS>
        inline static T* SafeNew(ARGS... args)
        {
            std::string name = typeid(T).name();
            T* obj;
            try
            {
                obj = new T(args...);
            } catch (const std::bad_alloc& e)
            {
                LOG_ERROR("Error allocating {}, reason: {}", name, e.what());
                RUNTIME_EXCEPTION("Error allocating {}, reason: {}", name, e.what());
            }
#ifndef NDEBUG


            if (!allocMap.contains(name))
            {
                allocMap[name] = 0;
            }
            allocMap[name]++;
#endif
            return obj;
        }

        template<typename T>
        inline static T* SafeNewArray(unsigned int size)
        {
            std::string name = "array of " + std::string(typeid(T).name());
            T* obj;
            try
            {
                obj = new T[size];
            } catch (const std::bad_alloc& e)
            {
                LOG_ERROR("Error allocating {}, reason: {}", name, e.what());
                RUNTIME_EXCEPTION("Error allocating {}, reason: {}", name, e.what());
            }
#ifndef NDEBUG

            if (!allocMap.contains(name))
            {
                allocMap[name] = 0;
            }
            allocMap[name]++;
#endif
            return obj;
        }


        template<typename T>
        inline static void SafeDelete(T*& ptr)
        {
            if (ptr)
            {
#ifndef NDEBUG
                std::string name = typeid(*ptr).name();
                allocMap[name]--;
#endif
                delete ptr;
                ptr = nullptr;
            }
        }

        template<typename T>
        inline static void SafeDeleteArray(T*& ptr)
        {
            if (ptr)
            {
#ifndef NDEBUG
                std::string name = "array of " + std::string(typeid(*ptr).name());
                allocMap[name]--;
#endif
                delete[] ptr;
                ptr = nullptr;
            }
        }

    };


}
