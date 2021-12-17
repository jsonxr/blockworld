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

const char *vertexShaderSource =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
#else
    "#version 330 core\n"
#endif
    "layout (location = 0) in highp vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
#else
    "#version 330 core\n"
#endif
    "    out highp vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);\n"
    "}\n";

unsigned int shaderProgram;

WebGLRenderer::WebGLRenderer(std::shared_ptr<Window> window) : window(window) {
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

  int success;
  GLsizei logLength;
  GLchar log[MAX_LOG_LENGTH];

  std::shared_ptr<WebGLShader> vertexShader =
      std::make_unique<WebGLShader>(vertex, vertexShaderSource);
  GLuint vertexHandle = vertexShader->handle();
  // std::unique_ptr<WebGLShader> vertexShader{vertex, vertexShaderSource};

  std::shared_ptr<WebGLShader> fragmentShader =
      std::make_unique<WebGLShader>(fragment, fragmentShaderSource);
  // WebGLShader fragmentShader{fragment, fragmentShaderSource};
  GLuint fragmentHandle = fragmentShader->handle();

  std::vector<std::shared_ptr<WebGLShader>> shaders{vertexShader,
                                                    fragmentShader};
  WebGLProgram program{shaders};
  shaderProgram = program.handle();

  glUseProgram(shaderProgram);
  std::cout << "jason 3" << shaderProgram << std::endl;

  //----------------------------------------------------------------------------
  // Geometry
  //----------------------------------------------------------------------------
  float vertices[] = {
      0.5f,  0.5f,  0.0f,  // top right
      0.5f,  -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f   // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
  // Create Buffers
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glViewport(0, 0, window->width(), window->height());

  std::cout << "width=" << window->width() << "height=" << window->height()
            << std::endl;
}

void WebGLRenderer::render() {
  glClearColor(0.f, 0.0f, 0.0f, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glfwSwapBuffers(window->nativeWindow());
}

}  // namespace BlockWorld
