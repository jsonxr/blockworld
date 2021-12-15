cmake_minimum_required(VERSION 3.21)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)


# Conan package manager include
set(CONAN_CMAKE_CXX_STANDARD 20)
set(CONAN_COMPILER "cmake")
set(CONAN_COMPILER_VERSION "13.0")
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

include_directories(include)
list(APPEND SOURCES
        src/core.h
        src/core/Input.h
        src/core/Input.cpp
        src/core/Window.h
        src/core/Window.cpp
        src/main.cpp
        )

add_executable(minecraft ${SOURCES})
target_link_libraries(minecraft ${CONAN_LIBS})

if(EMSCRIPTEN)
    #set(EMCC_LINKER_FLAGS " -s WASM=1 -O3 -o ../index.js -s --pre-js pre-module.js --post-js post-module.js -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1")
    set(EMCC_LINKER_FLAGS "-O0 -s SAFE_HEAP=1 --bind -s WASM=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM_BIGINT=1 -std=c++20 -s -s ASSERTIONS=1 -s GL_ASSERTIONS=1")

    # Optimization flags for emcc
    # -O0
    # -O3 or
    # -Oz   but reduces code size even further, and may take longer to run. This can affect both wasm and JavaScript

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY dist)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY dist)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY dist)

    set(CMAKE_EXECUTABLE_SUFFIX .html)
    set_target_properties(minecraft PROPERTIES LINK_FLAGS ${EMCC_LINKER_FLAGS})
endif()
