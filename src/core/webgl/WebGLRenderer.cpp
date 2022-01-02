#include "WebGLRenderer.h"

#include "../../core.h"
#include "../BufferGeometry.h"
#include "WebGLProgram.h"
#include "WebGLShader.h"

namespace BlockWorld {

static GLuint VAO;
static GLuint VBO;
static GLuint EBO;

// unsigned int shaderProgram;

WebGLRenderer::WebGLRenderer() { glfwSwapInterval(1); }

void WebGLRenderer::render(const Window &window, Scene &scene, Camera &camera) {
  // glViewport(0, 0, window.width(), window.height());
  glClearColor(0.F, 0.F, 0.F, 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  //   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  const auto &nodes = scene.getNodes();
  for (const auto &node : nodes) {
    node->render(camera);
  }

  glfwSwapBuffers(window.nativeWindow());
}

}  // namespace BlockWorld
