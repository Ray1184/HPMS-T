cmake_minimum_required(VERSION 3.26)
project(Runtime)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SOURCES src/rt/Main.cpp)

add_executable(Runtime ${SOURCES})
target_link_libraries(Runtime PRIVATE BackendImpl)
target_compile_features(Runtime PRIVATE cxx_std_20)
target_include_directories(Runtime PUBLIC include)

if(WIN32)
    add_custom_command(
            TARGET Runtime
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Runtime>
            VERBATIM)
endif()

install(TARGETS Runtime)
message(STATUS "Module Runtime built successfully")