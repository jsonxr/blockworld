//
// Created by Jason Rowland on 12/15/21.
//

#ifndef BLOCKWORLD_WEBGLSHADER_H
#define BLOCKWORLD_WEBGLSHADER_H

#include <string>

#include "../../core.h"

namespace BlockWorld {

enum WebGLShaderType : GLenum {
  none = 0,
  fragment = GL_FRAGMENT_SHADER,
  vertex = GL_VERTEX_SHADER,
};

class WebGLShader {
 public:
  WebGLShader(WebGLShaderType type, const char* source);
  ~WebGLShader();
  [[nodiscard]] auto handle() const -> GLuint { return this->_handle; };

 private:
  GLuint _handle;
  WebGLShaderType _type;
  // Intentionally private or Unimplemented since we don't copy or move
  WebGLShader(const WebGLShader& other);                     // copy constructor
  auto operator=(const WebGLShader& other) -> WebGLShader&;  // copy assignment
  WebGLShader(WebGLShader&& other) noexcept                  // move constructor
      : _handle(std::exchange(other._handle, NULL)),
        _type(std::exchange(other._type, none)){};
  auto operator=(WebGLShader&& other) noexcept
      -> WebGLShader&  // move assignment
  {
    std::swap(_handle, other._handle);
    std::swap(_type, other._type);
    return *this;
  };
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_WEBGLSHADER_H
