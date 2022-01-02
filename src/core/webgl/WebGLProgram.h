#ifndef BLOCK_WORLD_WEBGLPROGRAM_H
#define BLOCK_WORLD_WEBGLPROGRAM_H

#include <array>

#include "WebGLShader.h"

namespace BlockWorld {

class WebGLProgram {
 public:
  WebGLProgram() = default;
  WebGLProgram(const WebGLShader& vertexShader,
               const WebGLShader& fragmentShader);
  ~WebGLProgram();
  [[nodiscard]] auto handle() const -> GLuint { return _handle; };
  [[nodiscard]] auto use() const noexcept -> bool;

  void debug();
  auto getUniformLocation(const char* name) const -> int;
  void setUniform(const std::string& name, const mat4& value) const;
  void setUniform(const std::string& name, const vec4& value) const;
  void setUniform(const std::string& name, int value) const;

  // Copy: not supported
  WebGLProgram(const WebGLProgram& other) = delete;    // copy constructor
  auto operator=(const WebGLProgram& other) = delete;  // copy assignment
  // Move
  WebGLProgram(WebGLProgram&& other) noexcept
      : _handle(std::exchange(other._handle, NULL)){};  // move constructor
  auto operator=(WebGLProgram&& other) noexcept -> WebGLProgram& {
    std::swap(_handle, other._handle);
    return *this;
  }

 private:
  GLuint _handle;
  std::vector<std::string> _uniforms{};
  std::vector<std::string> _attributes{};
};

}  // namespace BlockWorld

#endif  // BLOCK_WORLD_WEBGLPROGRAM_H
