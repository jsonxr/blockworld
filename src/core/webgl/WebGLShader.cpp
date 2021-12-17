//
// Created by Jason Rowland on 12/15/21.
//
#include "WebGLShader.h"

namespace BlockWorld {

WebGLShader::~WebGLShader() {
  if (_handle > 0) {
    glDeleteShader(_handle);
  }
}

WebGLShader::WebGLShader(WebGLShaderType type, const char* source)
    : _type(type), _handle(glCreateShader(type)) {
  // GLuint vertexShader;
  std::cout << "Creating type=" << type << "handle=" << this->_handle
            << std::endl;
  // const char* c_str = source.c_str();
  glShaderSource(this->_handle, 1, &source, nullptr);
  glCompileShader(this->_handle);

  // Check to see if it succeeded
  GLint isCompiled = GL_FALSE;
  glGetShaderiv(this->_handle, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    std::array<GLchar, MAX_LOG_LENGTH> log{};
    glGetShaderInfoLog(_handle, sizeof(log), nullptr, log.data());
    std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
              << log.data() << std::endl;

    glDeleteShader(_handle);
    _handle = 0;
  }
  std::cout << "done" << std::endl;
}

}  // namespace BlockWorld