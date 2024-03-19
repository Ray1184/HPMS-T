#include "base/ResourcesHandler.h"
#include "engine/resource/ResourceSupplierImpl.h"
#include "base/Memory.h"
#include "engine/RendererImpl.h"
#include "engine/GameRunnerImpl.h"
#include "engine/WindowImpl.h"
#include "testing/TestLogic.h"
#include "engine/FrameBufferImpl.h"
#include <iostream>


int main()
{
    hpms::WindowSettings settings;
    settings.fullscreen = false;
    settings.appName = "Test01";
    settings.vSync = false;
    settings.framerateLimit = 1000;
    settings.pixelationRatio = 3;
    settings.width = 320;
    settings.height = 200;
    auto* window = SAFE_NEW(hpms::WindowImpl, settings);
    auto* framebuffer = SAFE_NEW(hpms::FrameBufferImpl, 320, 200);
    auto* logic = SAFE_NEW(hpms::TestLogic);
    hpms::InputHandler* inputHandler = nullptr;
    auto* renderer = SAFE_NEW(hpms::RendererImpl);
    auto* runner = SAFE_NEW(hpms::GameRunnerImpl, window, framebuffer, logic, inputHandler, renderer);

    runner->Run();

    SAFE_DELETE(hpms::GameRunnerImpl, runner);
    SAFE_DELETE(hpms::RendererImpl, renderer);
    //SAFE_DELETE(hpms::InputHandler, inputHandler);
    SAFE_DELETE(hpms::TestLogic, logic);
    SAFE_DELETE(hpms::FrameBufferImpl, framebuffer);
    SAFE_DELETE(hpms::WindowImpl, window);


    std::stringstream dump = MEMORY_DUMP;
    std::cout << dump.str() << std::endl;
    return 0;

}