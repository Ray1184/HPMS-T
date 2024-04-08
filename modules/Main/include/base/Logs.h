#pragma once

#include <sstream>
#include <string>
#include <chrono>

// NOTE: trace is used in logic and rendering loops, DISABLE_TRACE is encouraged in final releases in order to avoid string format in each call
#ifndef DISABLE_TRACE
#define LOG_TRACE(msg, ...) hpms::Logs::Log(hpms::LogLevel::TRACE, __FUNCTION__, std::format(msg, __VA_ARGS__))
#else
#define LOG_TRACE(msg, ...)
#endif
#define LOG_DEBUG(msg, ...) hpms::Logs::Log(hpms::LogLevel::DEBUG, __FUNCTION__, std::format(msg, __VA_ARGS__))
#define LOG_INFO(msg, ...) hpms::Logs::Log(hpms::LogLevel::INFO, __FUNCTION__, std::format(msg, __VA_ARGS__))
#define LOG_WARN(msg, ...) hpms::Logs::Log(hpms::LogLevel::WARN, __FUNCTION__, std::format(msg, __VA_ARGS__))
#define LOG_ERROR(msg, ...) hpms::Logs::Log(hpms::LogLevel::ERROR, __FUNCTION__, std::format(msg, __VA_ARGS__))

#define START_TIMER() auto timerStart = std::chrono::high_resolution_clock::now()
#define END_TIMER() auto timerEnd = std::chrono::high_resolution_clock::now(); auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(timerEnd-timerStart)

namespace hpms
{
    enum LogLevel
    {
        TRACE = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4
    };

    class Logs
    {
    private:
        static std::string GetLevelDescription(LogLevel level);

        static void PrintLog(const std::string& message);

    public:
        static LogLevel logLevel;

        static void Log(LogLevel level, const std::string& caller, const std::string& message);
    };
}
