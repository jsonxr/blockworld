#ifndef BLOCKWORLD_WEBGLRENDERER_H
#define BLOCKWORLD_WEBGLRENDERER_H

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

#endif  // BLOCKWORLD_WEBGLRENDERER_H
