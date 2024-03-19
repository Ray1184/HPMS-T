#include "base/FileSystem.h"
#include "base/Utils.h"

std::vector<std::string> hpms::FileSystem::mountedArchives = std::vector<std::string>();



int hpms::FileSystem::MountFS(const std::string& pak)
{
    if (std::find(mountedArchives.begin(), mountedArchives.end(), pak) == mountedArchives.end())
    {
        PHYSFS_init(nullptr);
        mountedArchives.push_back(pak);
        LOG_DEBUG("Mounting archive {}", pak);
        return PHYSFS_mount(pak.c_str(), nullptr, 1);
    }
    return 0;
}

int hpms::FileSystem::UnmountFS(const std::string& pak)
{
    if (std::find(mountedArchives.begin(), mountedArchives.end(), pak) != mountedArchives.end())
    {
        PHYSFS_unmount(pak.c_str());
        mountedArchives.erase(std::remove(mountedArchives.begin(), mountedArchives.end(), pak), mountedArchives.end());
        LOG_DEBUG("Unmounting archive {}", pak);
        return PHYSFS_deinit();
    }
    return 0;
}

unsigned int hpms::FileSystem::GetResourceFileSize(const std::string& path)
{
    if (PHYSFS_exists(path.c_str()))
    {
        PHYSFS_file* file = PHYSFS_openRead(path.c_str());
        unsigned int fileLength = PHYSFS_fileLength(file);
        PHYSFS_close(file);
        return fileLength;
    } else
    {
        LOG_ERROR("Impossible to retrieve {} from mounted archive", path);
        RUNTIME_EXCEPTION("Impossible to retrieve {} from mounted archive", path);
    }
}

void hpms::FileSystem::LoadResource(const std::string& path, unsigned int fileLength, unsigned int* size, void* buffer)
{
    if (PHYSFS_exists(path.c_str()))
    {
        PHYSFS_file* file = PHYSFS_openRead(path.c_str());
        unsigned int lengthRead = PHYSFS_readBytes(file, buffer, fileLength);
        *size = lengthRead;
        PHYSFS_close(file);
    } else
    {
        LOG_ERROR("Impossible to retrieve {} from mounted archive.", path);
        RUNTIME_EXCEPTION("Impossible to retrieve {} from mounted archive.", path);

    }
}

void hpms::FileSystem::EnumerateFiles(std::vector<std::string>& list)
{
    PHYSFS_enumerate("", EnumerateCallback, &list);
}

PHYSFS_EnumerateCallbackResult
hpms::FileSystem::EnumerateCallback(void* data, const char* origDir, const char* filename)
{
    char fullPath[1024];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", origDir, filename);

    PHYSFS_Stat stat;
    if (PHYSFS_stat(fullPath, &stat) == 0)
    {
        LOG_ERROR("Cannot retrieve archive information, error: {}", PHYSFS_getLastError());
        RUNTIME_EXCEPTION("Cannot retrieve archive information, error: {}", PHYSFS_getLastError());
    }

    if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY)
    {
        PHYSFS_enumerate(fullPath, EnumerateCallback, data);
    }
    else
    {
        auto* fileList = static_cast<std::vector<std::string>*>(data);
        fileList->emplace_back(fullPath);
    }

    return PHYSFS_ENUM_OK;
}


