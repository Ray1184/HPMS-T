#pragma once

#include <string>
#include <vector>

namespace hpms
{
    class Strings
    {
    private:
        static unsigned long long uniqueCounter;
    public:
        static std::string ReplaceAll(const std::string& source, const std::string& from, const std::string& to);
        static std::string GetFilenameExtension(const std::string& filename);
        static void RandomString(char* s, int len);
        static std::vector<std::string> Split(const std::string& stringToSplit, const std::string& reg);
        static std::string GetFileName(const std::string& s);
        static std::string Trim(const std::string& s);
        static std::string UpperCase(std::string s);
        static std::string LowerCase(std::string s);
        static std::string UniqueId();
    };
}