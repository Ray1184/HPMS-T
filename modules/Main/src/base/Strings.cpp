#include "base/Strings.h"

#include <random>
#include <regex>
#include <filesystem>

unsigned long long hpms::Strings::uniqueCounter = 0;

std::string hpms::Strings::ReplaceAll(const std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while (std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    newString += source.substr(lastPos);

    return newString;
}

std::string hpms::Strings::GetFilenameExtension(const std::string& filename)
{
    const std::filesystem::path filePath(filename);
    return filePath.extension().string();
}

void hpms::Strings::RandomString(char* s, int len)
{
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    for (int i = 0; i < len; ++i)
    {
        s[i] = alphanum[dis(gen)];
    }

    s[len] = 0;
}

std::vector<std::string> hpms::Strings::Split(const std::string& stringToSplit, const std::string& reg)
{
    std::vector<std::string> elems;

    const std::regex rgx(reg);

    std::sregex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), rgx, -1);
    const std::sregex_token_iterator end;

    while (iter != end)
    {
        elems.push_back(*iter);
        ++iter;
    }

    return elems;
}

std::string hpms::Strings::GetFileName(const std::string& s)
{
    const std::filesystem::path filePath(s);
    return filePath.filename().string();
}

std::string hpms::Strings::Trim(const std::string& s)
{
    const auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c)
    {
        return std::isspace(c);
    });
    const auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c)
    {
        return std::isspace(c);
    }).base();
    return wsback <= wsfront ? std::string() : std::string(wsfront, wsback);
}

std::string hpms::Strings::UpperCase(std::string s)
{
    for (char& l: s)
    {
        l = toupper(l);
    }
    return s;
}

std::string hpms::Strings::LowerCase(std::string s)
{
    for (char& l: s)
    {
        l = tolower(l);
    }
    return s;
}

std::string hpms::Strings::UniqueId()
{
    return std::to_string(uniqueCounter++);
}
