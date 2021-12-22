//
// Created by Jason Rowland on 12/17/21.
//

#ifndef BLOCKWORLD_MATERIAL_H
#define BLOCKWORLD_MATERIAL_H

#include <regex>

#include "webgl/WebGLProgram.h"

namespace BlockWorld {

class Material {
 public:
  Material();
  [[nodiscard]] auto getProgram() const -> const WebGLProgram& {
    return _program;
  }

  // Copy: not supported
  Material(const Material& other) = delete;        // copy constructor
  auto operator=(const Material& other) = delete;  // copy assignment
  // Move
  Material(Material&& other) noexcept
      : _program(std::exchange(other._program, WebGLProgram{})){};
  auto operator=(Material&& other) noexcept -> Material& {
    std::swap(_program, other._program);
    return *this;
  }

 private:
  WebGLProgram _program;
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_MATERIAL_H
