#pragma once

#include <string>
#include <functional>

namespace hpms
{
    typedef const std::function<void(const std::string&)> FileProcessorCallback;
    class Files
    {
    public:
        static std::string GetAbsolutePath(const std::string& relativePath);

        static void ProcessFileLines(const std::string& fileName, FileProcessorCallback& callback);

        static std::string ReadFile(const std::string& fileName);

        static bool FileExists(const std::string& fileName);

        static void WriteStringData(const std::string& fileName, const std::string& data);

        static void WriteLinesToFile(const std::string& outputFile, const std::vector<std::string>& lines);

    };
}