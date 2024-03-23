#include "base/PacksHandler.h"
#include "base/Utils.h"
#include "base/FileSystem.h"

#include <string>


void hpms::PacksHandler::ProcessPack(const std::string& pakId,
                                     ArchiveProcessorCallback& callback)
{

    FileSystem::MountFS(pakId);
    std::vector<std::string> files;
    FileSystem::EnumerateFiles(files);

      if (files.empty())
    {
        LOG_ERROR("Pack {} is empty or does not exists", pakId);
        RUNTIME_EXCEPTION("Pack {} is empty or does not exists", pakId);
    }

    for (auto& res: files)
    {
        const unsigned int fileLength = FileSystem::GetResourceFileSize(res);
        auto resBuffer = SAFE_NEW_ARRAY(char, fileLength);
        unsigned int size;
        FileSystem::LoadResource(res, fileLength, &size, resBuffer);
        callback(resBuffer, size, res);
        SAFE_DELETE_ARRAY(char, resBuffer);
    }
    FileSystem::UnmountFS(pakId);

}
