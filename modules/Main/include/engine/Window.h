#pragma once

#include <string>

namespace hpms
{
    struct WindowSettings
    {
        std::string appName;
        unsigned int width;
        unsigned int height;
        bool fullscreen;
        bool vSync;
        unsigned int pixelationRatio;
        unsigned int framerateLimit;
    };

    class Window
    {
    public:
        virtual const WindowSettings& GetSettings() const = 0;
    };
}