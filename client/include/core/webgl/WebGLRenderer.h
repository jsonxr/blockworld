#ifndef APP_WEBGLRENDERER_H
#define APP_WEBGLRENDERER_H

#include <map>

#include "core/BufferGeometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/Window.h"
#include "core/webgl/WebGLProgram.h"

namespace app {

class WebGLRenderer {
 public:
  WebGLRenderer();

  static void render(const Window &window, Scene &scene, Camera &camera);
};

}  // namespace app

#endif  // APP_WEBGLRENDERER_H
