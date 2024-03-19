#pragma once

#include "base/Logs.h"

#include <stdexcept>
#include <format>

#define RUNTIME_EXCEPTION(msg, ...)                                  \
    const std::string& errorMessage = std::format(msg, __VA_ARGS__); \
    throw hpms::AppError(errorMessage);

namespace hpms
{

    class AppError : public std::runtime_error
    {
    public:
        explicit AppError(const std::string& message) : runtime_error(message)
        {}

        explicit AppError(const char* message) : runtime_error(message)
        {}

    };
}