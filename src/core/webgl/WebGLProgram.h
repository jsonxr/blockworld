//
// Created by Jason Rowland on 12/15/21.
//

#ifndef BLOCKWORLD_WEBGLPROGRAM_H
#define BLOCKWORLD_WEBGLPROGRAM_H

#include <array>

#include "WebGLShader.h"

namespace BlockWorld {

class WebGLProgram {
 public:
  explicit WebGLProgram(
      const std::vector<std::shared_ptr<WebGLShader>>& shaders);
  ~WebGLProgram();
  [[nodiscard]] auto handle() const -> GLuint { return _handle; };

 private:
  GLuint _handle;
  // Intentionally Unimplemented since we can't copy or move
  WebGLProgram(const WebGLProgram& other);   // copy constructor
  auto operator=(const WebGLProgram& other)  // copy assignment
      -> WebGLProgram&;
  WebGLProgram(WebGLProgram&& other) noexcept  // move constructor
      : _handle(std::exchange(other._handle, NULL)){};
  auto operator=(WebGLProgram&& other) noexcept  // move assignment
      -> WebGLProgram& {
    std::swap(_handle, other._handle);
    return *this;
  };
};

}  // namespace BlockWorld
// namespace BlockWorld
#endif  // BLOCKWORLD_WEBGLPROGRAM_H
