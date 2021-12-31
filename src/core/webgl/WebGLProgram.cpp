#include "WebGLProgram.h"

#include <array>
#include <glm/gtc/type_ptr.hpp>

namespace BlockWorld {

WebGLProgram::WebGLProgram(const WebGLShader& vertexShader,
                           const WebGLShader& fragmentShader)
    : _handle(glCreateProgram()) {
  glAttachShader(_handle, vertexShader.handle());
  glAttachShader(_handle, fragmentShader.handle());
  glLinkProgram(_handle);
  glUseProgram(_handle);

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

  std::cout << "created WebGLProgram " << _handle << std::endl;
}

WebGLProgram::~WebGLProgram() {
  if (_handle > 0) {
    std::cout << "~WebGLProgram " << _handle << std::endl;
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

auto WebGLProgram::getUniformLocation(const char* name) const -> int {
  auto loc = glGetUniformLocation(_handle, name);
  if (loc < 0) {
    std::cerr << "Uniform not found for " << name << std::endl;
  }

  return loc;
}

void WebGLProgram::setUniform(const std::string& name,
                              const mat4& value) const {
  auto loc = getUniformLocation(name.c_str());
  if (loc >= 0) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
  }
}

void WebGLProgram::setUniform(const std::string& name,
                              const vec4& value) const {
  auto loc = getUniformLocation(name.c_str());
  if (loc >= 0) {
    glUniform4f(loc, value[0], value[1], value[2], value[3]);
  }
}

void WebGLProgram::setUniform(const std::string& name, const int value) const {
  auto loc = getUniformLocation(name.c_str());
  if (loc >= 0) {
    glUniform1i(loc, value);
  }
}

}  // namespace BlockWorld