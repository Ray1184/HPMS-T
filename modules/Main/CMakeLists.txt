cmake_minimum_required(VERSION 3.26)
project(Main)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(PHYSFS
        GIT_REPOSITORY https://github.com/icculus/physfs
        GIT_TAG release-3.2.0)
FetchContent_MakeAvailable(PHYSFS)

set(SOURCES
        src/base/ResourcesHandler.cpp
        src/base/FileSystem.cpp
        src/base/PacksHandler.cpp
        src/base/Files.cpp
        src/base/Strings.cpp
        src/base/Logs.cpp
        src/engine/renderable/PictureData.cpp
        src/engine/renderable/SpriteData.cpp
        src/engine/renderable/TilesChunkData.cpp
        src/ecs/system/RenderSystem.cpp)

add_library(Main ${SOURCES})
target_include_directories(Main PUBLIC include)
target_link_libraries(Main PUBLIC physfs-static)
target_compile_features(Main PRIVATE cxx_std_20)
message(STATUS "Module Main built successfully")