#include "engine/WindowImpl.h"
#include "base/Utils.h"

hpms::WindowImpl::WindowImpl(const WindowSettings& settings) : settings(settings)
{
    const auto style = settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    sfmlWindow = SAFE_NEW(sf::RenderWindow, sf::VideoMode(settings.width * settings.pixelationRatio, settings.height * settings.pixelationRatio), settings.appName, style);
    sfmlWindow->setVerticalSyncEnabled(settings.vSync);
    sfmlWindow->setFramerateLimit(settings.framerateLimit);
    sf::View sfView = sfmlWindow->getView();
    sfView.setSize(static_cast<float>(settings.width), static_cast<float>(settings.height));
    sfmlWindow->setView(sfView);
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
