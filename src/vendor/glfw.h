//
// Created by Jason Rowland on 1/1/22.
//

#ifndef BLOCK_WORLD_GLFW_H
#define BLOCK_WORLD_GLFW_H

// Glad and GLFW
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#endif  // BLOCK_WORLD_GLFW_H
