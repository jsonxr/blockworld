//
// Created by Jason Rowland on 12/14/21.
//

#ifndef BLOCKWORLD_WEBGLRENDERER_H
#define BLOCKWORLD_WEBGLRENDERER_H

#include "../BufferGeometry.h"
#include "../Camera.h"
#include "../Scene.h"
#include "../Window.h"
#include "WebGLProgram.h"

namespace BlockWorld {

class WebGLRenderer {
 public:
  WebGLRenderer();
  ~WebGLRenderer();
  static void compile(Scene& scene);
  static void render(const Window& window, Scene& scene, Camera& camera);

  // Copy: not supported
  WebGLRenderer(const WebGLRenderer& other) = delete;
  auto operator=(const WebGLRenderer& other) = delete;
  // Move
  WebGLRenderer(WebGLRenderer&& other) noexcept
      : program(std::exchange(other.program, WebGLProgram{})){};
  auto operator=(WebGLRenderer&& other) noexcept -> WebGLRenderer& {
    std::swap(program, other.program);
    return *this;
  }

 private:
  // Window& window;
  WebGLProgram program{};
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_WEBGLRENDERER_H
