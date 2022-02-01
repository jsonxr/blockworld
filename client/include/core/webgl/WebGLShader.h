#ifndef APP_WEBGLSHADER_H
#define APP_WEBGLSHADER_H

#include <string>

#include "core.h"

namespace app {

enum class WebGLShaderType : GLenum {
  kFragment = GL_FRAGMENT_SHADER,
  kVertex = GL_VERTEX_SHADER,
};

class WebGLShader {
 public:
  WebGLShader() = default;
  WebGLShader(WebGLShaderType type, const char *source);
  ~WebGLShader();
  [[nodiscard]] auto handle() const -> GLuint { return this->handle_; };

  // Copy: not supported
  WebGLShader(const WebGLShader &other) = delete;
  auto operator=(const WebGLShader &other) = delete;
  // Move
  WebGLShader(WebGLShader &&other) noexcept
      : handle_(std::exchange(other.handle_, NULL)){};
  auto operator=(WebGLShader &&other) noexcept -> WebGLShader & {
    std::swap(handle_, other.handle_);
    return *this;
  }

 private:
  GLuint handle_{0};
};

}  // namespace app

#endif  // APP_WEBGLSHADER_H
