cmake_minimum_required(VERSION 3.26)
project(HPMS_T)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(modules/Main)
add_subdirectory(modules/BackendImpl)
add_subdirectory(modules/Runtime)
add_subdirectory(modules/Tests)
message(STATUS "All modules built successfully")