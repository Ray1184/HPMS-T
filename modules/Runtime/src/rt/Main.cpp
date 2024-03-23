#include "base/ResourcesHandler.h"
#include "engine/resource/ResourceSupplierImpl.h"
#include "base/Memory.h"
#include "engine/Renderer.h"
#include "engine/RendererImpl.h"
#include "engine/GameRunner.h"
#include "engine/GameRunnerImpl.h"
#include <iostream>


int main()
{
    auto* resSupplier = SAFE_NEW(hpms::ResourceSupplierImpl);
    hpms::ResourcesHandler::PreloadResources("pak1.zip", resSupplier);
    hpms::Texture* tex = hpms::ResourcesHandler::Provide<hpms::Texture>("pak1.zip", "/textures/test.png");
    hpms::ResourcesHandler::UnloadResources("pak1.zip", resSupplier);
    SAFE_DELETE(hpms::ResourceSupplierImpl, resSupplier);


    const std::stringstream dump = MEMORY_DUMP;
    std::cout << dump.str() << std::endl;


}