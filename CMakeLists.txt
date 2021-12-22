cmake_minimum_required(VERSION 3.21)
project(blockworld)

set(CMAKE_CXX_STANDARD 20)


# Conan package manager include
set(CONAN_CMAKE_CXX_STANDARD 20)
set(CONAN_COMPILER "cmake")
set(CONAN_COMPILER_VERSION "13.0")
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

include_directories(include)
list(APPEND SOURCES
        # src/core/webgl
        src/core/webgl/WebGLProgram.h src/core/webgl/WebGLProgram.cpp
        src/core/webgl/WebGLRenderer.h src/core/webgl/WebGLRenderer.cpp
        src/core/webgl/WebGLShader.h src/core/webgl/WebGLShader.cpp
        # src/core
        src/core/BoxGeometry.h src/core/BoxGeometry.cpp
        src/core/BufferGeometry.h src/core/BufferGeometry.cpp
        src/core/Camera.h src/core/Camera.cpp
        src/core/Input.h src/core/Input.cpp
        src/core/Material.h src/core/Material.cpp
        src/core/Mesh.h src/core/Mesh.cpp
        src/core/Scene.h src/core/Scene.cpp
        src/core/Window.h src/core/Window.cpp
        # src
        src/core.h
        src/main.cpp
        )

add_executable(blockworld ${SOURCES} src/stb.cpp src/core/Assets.cpp src/core/Assets.h)
target_link_libraries(blockworld ${CONAN_LIBS})

if (EMSCRIPTEN)
    #set(EMCC_LINKER_FLAGS " -s WASM=1 -O3 -o ../index.js -s --pre-js pre-module.js --post-js post-module.js -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1")

    # Optimization flags for emcc
    # https://emscripten.org/docs/optimizing/Optimizing-Code.html
    # -O0 No optimizations (default)
    # -O3 or
    # -Oz   but reduces code size even further, and may take longer to run. This can affect both wasm and JavaScript
    # --bind Embind is used to bind C++ functions and classes to JavaScript, so that the compiled code can be used in a natural way by “normal” JavaScript. Embind also supports calling JavaScript classes from C++.
    # --embed-file <file> Specify a file (with path) to embed inside the generated JavaScript.
    # -gsource-map enerate a source map using LLVM debug information
    # -Wwarn-absolute-paths
    # --cpuprofiler Use this to perform cursory interactive performance profiling
    # --memoryprofiler Embeds a memory allocation tracker onto the generated page. Use this to profile the application usage of the Emscripten HEAP
    # --threadprofiler Embeds a thread activity profiler onto the generated page. Use this to profile the application usage of pthreads when targeting multithreaded builds (-s USE_PTHREADS=1/2)


    # Optimize WebGL
    # https://emscripten.org/docs/optimizing/Optimizing-WebGL.html
    # FULL_ES3= This emulation is expected to hurt performance.  if one needs to render from client side memory, or the use of glMapBuffer*() API is needed

    # Debugging
    # https://emscripten.org/docs/porting/Debugging.html
    # ASSERTIONS=1 if disabled, it also disables Stack_overflow_check
    # DEMANGLE_SUPPORT=1 links in code to automatically demangle stack traces, that is, emit human-readable C++ function names
    # SAFE_HEAP (adds additional memory checks and give clear errors during debug)
    # SAFE_HEAP_LOG (writes safe heap operations
    # STACK_OVERFLOW_CHECK=2 enables slightly more detailed stack guard checks, which can give a more precise callstack at the expense of some performance

    set(EMCC_LINKER_FLAGS "-O0 --bind -s WASM=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s USE_GLFW=3 -s WASM_BIGINT=1 -std=c++${CMAKE_CXX_STANDARD} --embed-file ${PROJECT_SOURCE_DIR}/assets@/assets -s ASSERTIONS=1 -s DEMANGLE_SUPPORT=1 -s GL_ASSERTIONS=1")

    set(CMAKE_EXECUTABLE_SUFFIX .html)
    set_target_properties(blockworld PROPERTIES LINK_FLAGS ${EMCC_LINKER_FLAGS})
endif ()
