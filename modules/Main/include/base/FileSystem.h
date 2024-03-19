#pragma once

#include <physfs.h>
#include <unordered_set>
#include <string>
#include <functional>
#include <vector>

namespace hpms
{
    class FileSystem
    {
    private:
        static std::vector<std::string> mountedArchives;
        static PHYSFS_EnumerateCallbackResult EnumerateCallback(void* data, const char* origDir, const char* filename);
    public:
        static int MountFS(const std::string& pak);
        static int UnmountFS(const std::string& pak);
        static void LoadResource(const std::string& path, unsigned int fileLength, unsigned int* size, void* buffer);
        static unsigned int GetResourceFileSize(const std::string& path);
        static void EnumerateFiles(std::vector<std::string>& list);
    };
}