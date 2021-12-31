#ifndef BLOCKWORLD_WEBGLSHADER_H
#define BLOCKWORLD_WEBGLSHADER_H

#include <string>

#include "../../core.h"

namespace BlockWorld {

enum class WebGLShaderType : GLenum {
  fragment = GL_FRAGMENT_SHADER,
  vertex = GL_VERTEX_SHADER,
};

class WebGLShader {
 public:
  WebGLShader() : _handle(0){};
  WebGLShader(WebGLShaderType type, const char* source);
  ~WebGLShader();
  [[nodiscard]] auto handle() const -> GLuint { return this->_handle; };

  // Copy: not supported
  WebGLShader(const WebGLShader& other) = delete;
  auto operator=(const WebGLShader& other) = delete;
  // Move
  WebGLShader(WebGLShader&& other) noexcept
      : _handle(std::exchange(other._handle, NULL)){};
  auto operator=(WebGLShader&& other) noexcept -> WebGLShader& {
    std::swap(_handle, other._handle);
    return *this;
  }

 private:
  GLuint _handle;
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_WEBGLSHADER_H
