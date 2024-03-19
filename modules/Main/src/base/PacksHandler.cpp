#include "base/PacksHandler.h"
#include "base/Utils.h"
#include "base/FileSystem.h"

#include <string>


void hpms::PacksHandler::ProcessPack(const std::string& pakId,
                                     ArchiveProcessorCallback& callback)
{

    hpms::FileSystem::MountFS(pakId);

    std::vector<std::string> files;
    hpms::FileSystem::EnumerateFiles(files);

    for (auto& res: files)
    {
        unsigned int fileLength = hpms::FileSystem::GetResourceFileSize(res);
        auto resBuffer = SAFE_NEW_ARRAY(char, fileLength);
        unsigned int size;
        hpms::FileSystem::LoadResource(res, fileLength, &size, resBuffer);
        callback(resBuffer, size, res);
        SAFE_DELETE_ARRAY(char, resBuffer);
    }
    hpms::FileSystem::UnmountFS(pakId);

}
