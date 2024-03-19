cmake_minimum_required(VERSION 3.26)
project(Tests)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SOURCES src/testing/TestRunner.cpp)

add_executable(Tests ${SOURCES})
target_link_libraries(Tests PRIVATE BackendImpl)
target_compile_features(Tests PRIVATE cxx_std_20)
target_include_directories(Tests PUBLIC include)

if(WIN32)
    add_custom_command(
            TARGET Tests
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Tests>
            VERBATIM)
endif()

install(TARGETS Tests)
message(STATUS "Module Tests built successfully")