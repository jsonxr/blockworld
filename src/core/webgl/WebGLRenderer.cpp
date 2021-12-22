//
// Created by Jason Rowland on 12/14/21.
//
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

WebGLRenderer::~WebGLRenderer() { std::cout << "~WebGLRenderer" << std::endl; }

WebGLRenderer::WebGLRenderer() { glfwSwapInterval(1); }

void WebGLRenderer::compile(Scene &scene) {
  const auto &meshes = scene.getMeshes();
  std::cout << "renderer compile mesh.size=" << meshes.size() << std::endl;

  for (const auto &mesh : scene.getMeshes()) {
    mesh->compile();
  }
}

void WebGLRenderer::render(const Window &window, Scene &scene, Camera &camera) {
  // glViewport(0, 0, window.width(), window.height());
  glClearColor(0.F, 0.F, 0.F, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  const auto &meshes = scene.getMeshes();
  for (const auto &mesh : scene.getMeshes()) {
    mesh->render();
  }
  //
  //  program.use();
  //  glBindVertexArray(VAO);
  //  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //
  glfwSwapBuffers(window.nativeWindow());
}

}  // namespace BlockWorld
