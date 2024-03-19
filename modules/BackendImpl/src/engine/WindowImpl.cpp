#include "engine/WindowImpl.h"

hpms::WindowImpl::WindowImpl(const WindowSettings& settings) : settings(settings)
{
    auto style = settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    sfmlWindow = SAFE_NEW(sf::RenderWindow, sf::VideoMode(settings.width * settings.pixelationRatio, settings.height * settings.pixelationRatio), settings.appName, style);
    sfmlWindow->setVerticalSyncEnabled(settings.vSync);
    sfmlWindow->setFramerateLimit(settings.framerateLimit);
}


sf::RenderWindow* hpms::WindowImpl::GetNative()
{
    return sfmlWindow;
}

const hpms::WindowSettings& hpms::WindowImpl::GetSettings() const
{
    return settings;
}

hpms::WindowImpl::~WindowImpl()
{
    SAFE_DELETE(sf::RenderWindow, sfmlWindow);
}
