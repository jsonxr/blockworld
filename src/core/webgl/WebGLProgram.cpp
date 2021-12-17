//
// Created by Jason Rowland on 12/15/21.
//

#include "WebGLProgram.h"

#include <array>

namespace BlockWorld {

WebGLProgram::~WebGLProgram() {
  if (_handle > 0) {
    glDeleteProgram(_handle);
  }
}

WebGLProgram::WebGLProgram(
    const std::vector<std::shared_ptr<WebGLShader>>& shaders)
    : _handle(glCreateProgram()) {
  for (const auto& shader : shaders) {
    glAttachShader(_handle, shader->handle());
  }
  glLinkProgram(_handle);

  GLint isCompiled = GL_FALSE;
  glGetProgramiv(_handle, GL_LINK_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    std::array<GLchar, MAX_LOG_LENGTH> log{};
    glGetProgramInfoLog(_handle, sizeof(log), nullptr, log.data());
    std::cout << "ERROR::program::COMPILATION_FAILED\n"
              << log.data() << std::endl;
    glDeleteProgram(_handle);
    _handle = 0;
  }
}

}  // namespace BlockWorld