#include "base/Logs.h"

#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

hpms::LogLevel hpms::Logs::logLevel = hpms::LogLevel::INFO;


void hpms::Logs::Log(hpms::LogLevel level, const std::string& caller, const std::string& message)
{
    if (level >= logLevel)
    {
        std::stringstream ss;
        std::time_t t = std::time(nullptr);
        std::tm tm = {};
        localtime_s(&tm, &t);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        std::stringstream formattedCaller;
        formattedCaller << std::left << std::setfill(' ') << std::setw(60) << caller;
        ss << GetLevelDescription(level);
        ss << "|" << buffer;
        ss << "|" << formattedCaller.str().substr(0, 50);
        ss << "|" << message;
        PrintLog(ss.str());
    }
}

std::string hpms::Logs::GetLevelDescription(hpms::LogLevel level)
{
    switch (level)
    {
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO ";
        case LogLevel::WARN:
            return "WARN ";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "N/A  ";
    }
}

void hpms::Logs::PrintLog(const std::string& message)
{
    std::cout << message << std::endl;
}
