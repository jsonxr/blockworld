#ifndef BLOCK_WORLD_WEBGLRENDERER_H
#define BLOCK_WORLD_WEBGLRENDERER_H

#include <map>

#include "core/BufferGeometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/Window.h"
#include "core/webgl/WebGLProgram.h"

namespace block_world {

class WebGLRenderer {
 public:
  WebGLRenderer();

  static void render(const Window &window, Scene &scene, Camera &camera);
};

}  // namespace block_world

#endif  // BLOCK_WORLD_WEBGLRENDERER_H
