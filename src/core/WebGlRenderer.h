//
// Created by Jason Rowland on 12/14/21.
//

#ifndef BLOCKWORLD_WEBGLRENDERER_H
#define BLOCKWORLD_WEBGLRENDERER_H

#include "Window.h"

namespace BlockWorld {

class WebGlRenderer {
 private:
  std::shared_ptr<Window> window;

 public:
  WebGlRenderer(std::shared_ptr<Window> window);
  void render();
};
}  // namespace BlockWorld

#endif  // BLOCKWORLD_WEBGLRENDERER_H
