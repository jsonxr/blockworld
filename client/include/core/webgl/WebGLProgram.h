#ifndef BLOCK_WORLD_WEBGLPROGRAM_H
#define BLOCK_WORLD_WEBGLPROGRAM_H

#include <array>

#include "core/webgl/WebGLShader.h"

namespace block_world {

class WebGLProgram {
 public:
  WebGLProgram() = default;
  WebGLProgram(const WebGLShader &vertexShader,
               const WebGLShader &fragmentShader);
  ~WebGLProgram();
  [[nodiscard]] auto handle() const -> GLuint { return handle_; };
  [[nodiscard]] auto use() const noexcept -> bool;

  void debug();
  auto get_uniform_location(const char *name) const -> int;
  static void set_uniform(int loc, const mat4 &value);
  static void set_uniform(int loc, const vec4 &value);
  static void set_uniform(int loc, int value);

  // Copy: not supported
  WebGLProgram(const WebGLProgram &other) = delete;    // copy constructor
  auto operator=(const WebGLProgram &other) = delete;  // copy assignment
  // Move
  WebGLProgram(WebGLProgram &&other) noexcept
      : handle_(std::exchange(other.handle_, NULL)){};  // move constructor
  auto operator=(WebGLProgram &&other) noexcept -> WebGLProgram & {
    std::swap(handle_, other.handle_);
    return *this;
  }

 private:
  GLuint handle_;
  std::vector<std::string> uniforms_{};
  std::vector<std::string> attributes_{};
};

}  // namespace block_world

#endif  // BLOCK_WORLD_WEBGLPROGRAM_H
