//
// Created by Jason Rowland on 12/15/21.
//

#ifndef BLOCKWORLD_SHADERMATERIAL_H
#define BLOCKWORLD_SHADERMATERIAL_H

#include "../../core.h"

namespace BlockWorld {

class ShaderMaterial {
 private:
 public:
  std::string vertexShader{};
  std::string fragmentShader{};
};

}  // namespace BlockWorld
// namespace BlockWorld
#endif  // BLOCKWORLD_SHADERMATERIAL_H
