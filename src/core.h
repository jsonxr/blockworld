#ifndef MINECRAFT_CLONE_CORE_H
#define MINECRAFT_CLONE_CORE_H

// Glad and GLFW
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include "linmath.h"

// Standard library stuff
#include <stdint.h>
#include <stdio.h>

#include <array>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

constexpr int MAX_LOG_LENGTH = 1024;

#endif