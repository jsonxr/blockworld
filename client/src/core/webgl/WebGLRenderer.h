#ifndef APP_WEBGLRENDERER_H
#define APP_WEBGLRENDERER_H

#include <map>

#include "../BufferGeometry.h"
#include "../Camera.h"
#include "../Scene.h"
#include "../Window.h"
#include "WebGLProgram.h"

namespace app {

class WebGLRenderer {
 public:
  WebGLRenderer();

  static void render(const Window &window, Scene &scene, Camera &camera);
};

}  // namespace app

#endif  // APP_WEBGLRENDERER_H
