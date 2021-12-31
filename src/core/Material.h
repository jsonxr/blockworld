#ifndef BLOCKWORLD_MATERIAL_H
#define BLOCKWORLD_MATERIAL_H

#include "webgl/WebGLProgram.h"

namespace BlockWorld {

class IMaterial {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~IMaterial() = default;
  // pure virtual function
  virtual void render() = 0;
};

class Material {
 public:
  explicit Material(const char* textureFilename = nullptr);
  ~Material() = default;
  void render();

  // Copy: not supported
  Material(const Material& other) = delete;        // copy constructor
  auto operator=(const Material& other) = delete;  // copy assignment
  // Move
  Material(Material&& other) noexcept
      : _program(std::exchange(other._program, WebGLProgram{})),
        _texture(std::exchange(other._texture, 0)){};
  auto operator=(Material&& other) noexcept -> Material& {
    std::swap(_program, other._program);
    std::swap(_texture, other._texture);
    return *this;
  }

 private:
  WebGLProgram _program{};
  GLuint _texture{0};
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_MATERIAL_H
