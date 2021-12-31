#include "Material.h"

#include <fstream>
#include <glm/ext.hpp>
#include <iostream>
#include <regex>

#include "Assets.h"
#include "Window.h"

namespace BlockWorld {

constexpr auto isPowerOf2(int value) -> bool {
  return ((value & (value - 1)) == 0) && (value != 0);
}

auto readAssetIntoString(const char* filename) -> std::string {
  std::string contents = Assets::loadString(filename);

  if (isEMSCRIPTEN()) {
    static const std::regex opengl_version{"#version 330 core"};
    contents = std::regex_replace(contents, opengl_version,
                                  "#version 300 es\n#define EMSCRIPTEN");
  }

  return contents;
}

Material::Material(const char* textureFilename) {
  std::string vertexShaderSource = readAssetIntoString("/shaders/vertex.glsl");
  std::string fragmentShaderSource =
      readAssetIntoString("/shaders/fragment.glsl");

  WebGLShader vertexShader{WebGLShaderType::vertex, vertexShaderSource.c_str()};
  WebGLShader fragmentShader{WebGLShaderType::fragment,
                             fragmentShaderSource.c_str()};
  _program = WebGLProgram{vertexShader, fragmentShader};

  // texture
  if (textureFilename == nullptr) {
    return;
  }

  auto png = Assets::loadPng(textureFilename);
  std::cout << "data: "
            << "texture=" << textureFilename << " height=" << png->height()
            << " width=" << png->width() << " channels=" << png->channels()
            << std::endl;
  // Performance, make sure we only use power of 2 textures
  if (!isPowerOf2(png->width()) || !isPowerOf2(png->height())) {
    std::cerr << "image not power of 2" << std::endl;
    exit(EXIT_FAILURE);  // NOLINT(concurrency-mt-unsafe)
  }

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glGenerateMipmap(GL_TEXTURE_2D);
  //_gl.SRGB8_ALPHA8 : _gl.RGBA8

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, png->width(), png->height(), 0,
               GL_RGBA, GL_UNSIGNED_BYTE, png->data());
  glBindTexture(GL_TEXTURE_2D, NULL);  // reset

  // if non power of 2
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // else mipmap
  // glGenerateMipmap(GL_TEXTURE_2D);

  // glBindTexture(GL_TEXTURE_2D, NULL);
}

void Material::render() {
  if (!_program.use()) {
    std::cerr << "WebGLMaterial::use program not available" << std::endl;
    return;
  }

  if (_texture != 0) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    //        glActiveTexture(GL_TEXTURE1);
    //        glBindTexture(GL_TEXTURE_2D, texture2);

    _program.setUniform("texture0", 0);
  }

  mat4 model = mat4(1.0F);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  mat4 view = mat4(1.0F);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  mat4 projection = glm::perspective(
      glm::radians(45.0F), (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT, 0.1F,
      100.0F);
  // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  //  trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

  _program.setUniform("model", model);
  _program.setUniform("view", view);
  _program.setUniform("projection", projection);
}

}  // namespace BlockWorld
