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

WebGLRenderer::WebGLRenderer() {
  glfwSwapInterval(1);

  //  std::vector<Vertex> vertices{
  //      //      Color                         Position
  //      Vertex{{0.9f, 0.1f, 0.12f, 1.0f}, {-0.5f, -0.5f, 0.0f}},
  //      Vertex{{0.1f, 0.9f, 0.12f, 1.0f}, {-0.5f, 0.5f, 0.0f}},
  //      Vertex{{0.12f, 0.9f, 0.1f, 1.0f}, {0.5f, 0.5f, 0.0f}},
  //
  //      Vertex{{0.9f, 0.1f, 0.12f, 1.0f}, {-0.5f, -0.5f, 0.0f}},
  //      Vertex{{0.12f, 0.9f, 0.1f, 1.0f}, {0.5f, 0.5f, 0.0f}},
  //      Vertex{{0.12f, 0.1f, 0.9f, 1.0f}, {0.5f, -0.5f, 0.0f}}};
  //  geometry.setVertices(vertices);

  //    WebGLShader vertexShader{vertex, vertexShaderSource};
  //    WebGLShader fragmentShader{fragment, fragmentShaderSource};

  //  int success;
  //  GLsizei logLength;
  //  GLchar log[MAX_LOG_LENGTH];
  //
  //  std::shared_ptr<WebGLShader> vertexShader = std::make_unique<WebGLShader>(
  //      WebGLShaderType::vertex, vertexShaderSource);
  //  GLuint vertexHandle = vertexShader->handle();
  //  // std::unique_ptr<WebGLShader> vertexShader{vertex, vertexShaderSource};
  //
  //  std::shared_ptr<WebGLShader> fragmentShader =
  //  std::make_unique<WebGLShader>(
  //      WebGLShaderType::fragment, fragmentShaderSource);
  //  // WebGLShader fragmentShader{fragment, fragmentShaderSource};
  //  GLuint fragmentHandle = fragmentShader->handle();
  //
  //  std::vector<std::shared_ptr<WebGLShader>> shaders{vertexShader,
  //                                                    fragmentShader};
  //
  //  program = WebGLProgram{shaders};
  //  program.use();

  // program.reset(std::make_unique<WebGLProgram>(shaders));
  //  program = WebGLProgram{shaders};

  // shaderProgram = program.handle();

  // glUseProgram(program.handle());
  //  std::cout << "jason 3" << shaderProgram << std::endl;

  //----------------------------------------------------------------------------
  // Geometry
  //----------------------------------------------------------------------------
  //  float vertices[] = {
  //      0.5f,  0.5f,  0.0f,  // top right
  //      0.5f,  -0.5f, 0.0f,  // bottom right
  //      -0.5f, -0.5f, 0.0f,  // bottom left
  //      -0.5f, 0.5f,  0.0f   // top left
  //  };
  //  unsigned int indices[] = {
  //      // note that we start from 0!
  //      0, 1, 3,  // first triangle
  //      1, 2, 3   // second triangle
  //  };
  //  // Create Buffers
  //  glGenBuffers(1, &EBO);
  //  glGenVertexArrays(1, &VAO);
  //  glGenBuffers(1, &VBO);
  //
  //  glBindVertexArray(VAO);
  //  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
  //               GL_STATIC_DRAW);
  //  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
  //                        (void *)nullptr);
  //  glEnableVertexAttribArray(0);
  //
  //  glViewport(0, 0, window->width(), window->height());
  //
  //  std::cout << "width=" << window->width() << "height=" << window->height()
  //            << std::endl;
}

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
