//
// Created by Jason Rowland on 12/14/21.
//

#ifndef BLOCKWORLD_WEBGLRENDERER_H
#define BLOCKWORLD_WEBGLRENDERER_H

#include "../BufferGeometry.h"
#include "../Window.h"

namespace BlockWorld {

class WebGLRenderer {
 private:
  std::shared_ptr<Window> window;

 public:
  explicit WebGLRenderer(std::shared_ptr<Window> window);
  void render();
};
}  // namespace BlockWorld

#endif  // BLOCKWORLD_WEBGLRENDERER_H
