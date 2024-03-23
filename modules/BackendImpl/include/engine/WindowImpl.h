#pragma once

#include "engine/Window.h"
#include "engine/NativeData.h"

#include <SFML/Graphics.hpp>

namespace hpms
{
    class WindowImpl : public Window, NativeData<sf::RenderWindow>
    {
    private:
        WindowSettings settings;
        sf::RenderWindow* sfmlWindow;

    public:
        explicit WindowImpl(const WindowSettings& settings);

        virtual ~WindowImpl();

        sf::RenderWindow* GetNative() override;

        virtual const WindowSettings& GetSettings() const override;
    };
}
