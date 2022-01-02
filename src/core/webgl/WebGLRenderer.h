#ifndef BLOCK_WORLD_WEBGLRENDERER_H
#define BLOCK_WORLD_WEBGLRENDERER_H

#include <map>

#include "../BufferGeometry.h"
#include "../Camera.h"
#include "../Scene.h"
#include "../Window.h"
#include "WebGLProgram.h"

namespace BlockWorld {

class WebGLRenderer {
 public:
  WebGLRenderer();

  void render(const Window& window, Scene& scene, Camera& camera);
};

}  // namespace BlockWorld

#endif  // BLOCK_WORLD_WEBGLRENDERER_H
