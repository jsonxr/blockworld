# BlockWorld clone

Following along with the [YouTube series](https://www.youtube.com/watch?v=HhH_9DnMBgw).

# Setup

Install

* [emscripten](https://emscripten.org/)
* [Conan package manager](https://conan.io/)

# CLion

* [CLion IDE](https://www.jetbrains.com/clion/)
* [CLion Conan plugin](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360008851580-How-to-use-Conan-Package-Manager-for-C-on-CLion-Mac)
* [GLSL Support plugin](https://plugins.jetbrains.com/plugin/6993-glsl-support)

```shell
# Install conan dependencies
conan install . -s build_type=Debug --install-folder=cmake-build-debug --build missing
# dont do below, click on that conan install at the bottom and then reload the cmake project in the ide
#cd cmake-build-debug && cmake ..
```

# Compile

```shell
# Debug dependencies
mkdir build
conan install . -s build_type=Debug -s compiler.libcxx=libc++ -s cppstd=17 --install-folder=build --build missing
# Release dependencies
# conan install . -s build_type=Release -s compiler.libcxx=libc++ -s cppstd=17 --install-folder=cmake-build-release --build missing
cd build
cmake .. && cmake --build .

# Run app...
bin/blockworld
```

# Wasm

Uses Experimental Features: [WebAssembly Roadmap](https://webassembly.org/roadmap/)

* Exceptions (Chrome, In progress: Firefox, No: Safari) - We just have to deal with crashes until this is supported
* Threads and atomics (Chrome, Firefox, In progress: Safari) - Not used yet, but we will want to...
* WebGPU

```shell
conan install . -s build_type=Debug -s compiler.libcxx=libc++ -s cppstd=17 --install-folder=build-wasm --build missing
cd build-wasm
emcmake cmake ..
cmake --build .

# Run app...
npx http-server bin  # This assumes node is installed...
open http://127.0.0.1:8080/blockworld.html

#emcc src/main.cpp -o cmake-build-wasm/index.html -Iinclude -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++17 -fwasm-exceptions
```

[wasm cmake dependencies](https://stackoverflow.com/questions/55869531/how-to-use-emscripten-with-cmake-for-project-dependencies)

### Exceptions

* [roadmap](https://webassembly.org/roadmap/)
* [zero cost exceptions](https://github.com/WebAssembly/design/issues/1078)
* [-fwasm-exceptions (enable wasm exceptions)](https://emscripten.org/docs/porting/exceptions.html)
* [-s DISABLE_EXCEPTION_CATCHING=0 (is this old?)](https://brionv.com/log/2019/10/24/exception-handling-in-emscripten-how-it-works-and-why-its-disabled-by-default/)

# Resources

* [Definitive Guide to Creating a Window | How to Code Minecraft Ep. 1](https://www.youtube.com/watch?v=HhH_9DnMBgw)
* [what is this link?](https://www.youtube.com/watch?v=sMs28KxbHiA)
* https://gist.github.com/ousttrue/0f3a11d5d28e365b129fe08f18f4e141
* [setup on mac. need to code sign?](https://giovanni.codes/opengl-setup-in-macos/)
* [Faithful 1.18 Resource Pack](https://faithful.team/faithful-1-18/)

# C++ Standard

https://en.cppreference.com/w/cpp/compiler_support

# Libraries

* [glfw - GL windowing library](https://www.glfw.org/):  zlib/libpng License
* [glad - GL bootstrap](https://github.com/Dav1dde/glad): MIT License
* [glm - GL Math](https://github.com/g-truc/glm): The Happy Bunny License or MIT License
* [tinygltf - GLTF file loading](https://github.com/syoyo/tinygltf): MIT License
* [stb - image processing](https://github.com/nothings/stb): MIT License or Public Domain

# TODO

* Modify cmake to recompile for asset change
    * [blog article](https://jeremimucha.com/2021/05/cmake-managing-resources/)
    * [gist](https://gist.github.com/jamcodes/f79b3be24ed40c6c224cc9e91d3061cc)
