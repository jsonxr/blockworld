#ifndef APP_GLFW_H
#define APP_GLFW_H

// Glad and GLFW
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#endif  // APP_GLFW_H
