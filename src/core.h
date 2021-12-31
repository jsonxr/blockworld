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

// include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//#include "linmath.h"

// Standard library stuff
#include <array>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;

constexpr int MAX_LOG_LENGTH = 1024;

#ifdef __EMSCRIPTEN__
constexpr auto isEMSCRIPTEN() -> bool { return true; }
#else
constexpr auto isEMSCRIPTEN() -> bool { return false; }
#endif

#endif