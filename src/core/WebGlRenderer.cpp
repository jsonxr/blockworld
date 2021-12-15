//
// Created by Jason Rowland on 12/14/21.
//

#include "WebGlRenderer.h"

namespace BlockWorld {

WebGlRenderer::WebGlRenderer(std::shared_ptr<Window> window) : window(window) {}

void WebGlRenderer::render() {
  glViewport(0, 0, window->width(), window->height());
  glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window->nativeWindow());
}

}  // namespace BlockWorld
