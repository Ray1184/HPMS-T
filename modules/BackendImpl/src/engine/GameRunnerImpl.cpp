#include "engine/GameRunnerImpl.h"
#include "engine/WindowImpl.h"

#include <SFML/System.hpp>

void hpms::GameRunnerImpl::Run()
{
    sf::Clock clock;
    auto* sfWindow = dynamic_cast<WindowImpl*>(window);
    logic->Init();
#ifndef NDEBUG
    sf::Clock secondClock;
    secondClock.restart();
    sfWindow->GetNative()->setTitle(window->GetSettings().appName + " [- FPS]");
#endif
    while (sfWindow->GetNative()->isOpen())
    {
        sf::Event event{};
        while (sfWindow->GetNative()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                sfWindow->GetNative()->close();
            }
        }
        logic->HandleInput(inputHandler);
        const float tpf = clock.restart().asSeconds();
#ifndef NDEBUG
        if (secondClock.getElapsedTime().asSeconds() > 1)
        {
            const int framerate = static_cast<int>(1 / tpf);
            sfWindow->GetNative()->setTitle(window->GetSettings().appName + " [" + std::to_string(framerate) + " FPS]");
            secondClock.restart();
        }
#endif
        logic->Update(tpf);
        logic->Render(renderer, window, framebuffer);
    }
    logic->Cleanup();
}

hpms::GameRunnerImpl::GameRunnerImpl(Window* window,
                                     FrameBuffer* framebuffer,
                                     GameLogic* logic,
                                     InputHandler* inputHandler,
                                     Renderer* renderer) : window(window),
                                                                 framebuffer(framebuffer),
                                                                 logic(logic),
                                                                 inputHandler(inputHandler),
                                                                 renderer(renderer)
{}
