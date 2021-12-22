//
// Created by Jason Rowland on 12/15/21.
//

#include "WebGLProgram.h"

#include <array>

namespace BlockWorld {

WebGLProgram::WebGLProgram(const WebGLShader& vertexShader,
                           const WebGLShader& fragmentShader)
    : _handle(glCreateProgram()) {
  glAttachShader(_handle, vertexShader.handle());
  glAttachShader(_handle, fragmentShader.handle());
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
    return;
  }

  std::cout << "WebGLProgram " << _handle << std::endl;
}

WebGLProgram::~WebGLProgram() {
  std::cout << "~WebGLProgram " << _handle << std::endl;
  if (_handle > 0) {
    glDeleteProgram(_handle);
    _handle = 0;
  }
}

auto WebGLProgram::use() const noexcept -> bool {
  if (_handle > 0) {
    glUseProgram(_handle);
  } else {
    std::cerr << "WebGLProgram can't use" << _handle << std::endl;
  }
  return _handle != 0U;
}

void WebGLProgram::setUniform(const std::string& name,
                              const vec4& value) const {
  glUniform4f(glGetUniformLocation(_handle, name.c_str()), value[0], value[1],
              value[2], value[3]);
}

}  // namespace BlockWorld