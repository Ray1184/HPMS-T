#include "base/Files.h"
#include "base/AppError.h"
#include "base/Strings.h"

#include <fstream>
#include <sstream>
#include <filesystem>


std::string hpms::Files::GetAbsolutePath(const std::string& relativePath)
{
    const auto dir = std::filesystem::weakly_canonical(relativePath);
    return dir.string();
}

void hpms::Files::ProcessFileLines(const std::string& fileName, FileProcessorCallback& callback)
{
    std::ifstream file(fileName);
    if (file)
    {
        for (std::string line; getline(file, line);)
        {
            callback(Strings::Trim(line));
        }
    } else
    {
        LOG_ERROR("Cannot open/read file with name {}", fileName);
        RUNTIME_EXCEPTION("Cannot open/read file with name {}", fileName);
    }
}

std::string hpms::Files::ReadFile(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (file)
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    LOG_ERROR("Cannot open/read file with name {}", fileName);
    RUNTIME_EXCEPTION("Cannot open/read file with name {}", fileName);
}

bool hpms::Files::FileExists(const std::string& fileName)
{
    std::ifstream file(fileName);
    const bool exists = file.good();
    file.close();
    return exists;
}

void hpms::Files::WriteStringData(const std::string& fileName, const std::string& data)
{
    std::ofstream out(fileName);
    out << data;
    out.close();
}

void hpms::Files::WriteLinesToFile(const std::string& outputFile, const std::vector<std::string>& lines)
{
    if (lines.empty())
    {
        return;
    }
    std::ofstream ostream(outputFile);
    for (auto& line: lines)
    {
        ostream << line << std::endl;
    }
    ostream.close();
}
