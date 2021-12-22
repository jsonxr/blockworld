//
// Created by Jason Rowland on 12/15/21.
//
#include "WebGLShader.h"

namespace BlockWorld {

WebGLShader::~WebGLShader() {
  std::cout << "~WebGLShader " << _handle << std::endl;
  if (_handle > 0) {
    glDeleteShader(_handle);
  }
}

WebGLShader::WebGLShader(WebGLShaderType type, const char* source)
    : _handle(glCreateShader(static_cast<GLenum>(type))) {
  std::cout << "WebGLShader " << _handle << std::endl;

  glShaderSource(this->_handle, 1, &source, nullptr);
  glCompileShader(this->_handle);

  // Check to see if it succeeded
  GLint isCompiled = GL_FALSE;
  glGetShaderiv(this->_handle, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    std::array<GLchar, MAX_LOG_LENGTH> log{};
    glGetShaderInfoLog(_handle, sizeof(log), nullptr, log.data());
    std::cerr << "ERROR::SHADER::"
              << "::COMPILATION_FAILED\n"
              << log.data() << std::endl;

    glDeleteShader(_handle);
    _handle = 0;
  }
}

}  // namespace BlockWorld