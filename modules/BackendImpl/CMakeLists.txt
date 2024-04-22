cmake_minimum_required(VERSION 3.26)
project(BackendImpl)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SOURCES
        src/engine/resource/TextureImpl.cpp
        src/engine/WindowImpl.cpp
        src/engine/GameRunnerImpl.cpp
        src/engine/RendererImpl.cpp
        src/engine/FrameBufferImpl.cpp
        src/engine/workflow/PictureDataRenderingWorkflow.cpp
        src/engine/workflow/TilesChunkDataRenderingWorkflow.cpp
        src/engine/workflow/SpriteDataRenderingWorkflow.cpp
        src/engine/workflow/VertexBufferProvider.cpp)

add_library(BackendImpl ${SOURCES})
target_link_libraries(BackendImpl PUBLIC sfml-graphics PUBLIC Main)
target_compile_features(BackendImpl PRIVATE cxx_std_20)
target_include_directories(BackendImpl PUBLIC include)
message(STATUS "Module BackendImpl built successfully")