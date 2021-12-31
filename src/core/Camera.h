#ifndef BLOCKWORLD_CAMERA_H
#define BLOCKWORLD_CAMERA_H

#include <glm/ext.hpp>

#include "Window.h"

namespace BlockWorld {

constexpr float FOV = 45.0F;
constexpr float Z_NEAR = 0.1F;
constexpr float Z_FAR = 100.0F;

class Camera {
 public:
  Camera() {
    float aspect = (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT;
    _proj = glm::perspective(glm::radians(FOV), aspect, Z_NEAR, Z_FAR);
  }

 private:
  mat4 _proj{};
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_CAMERA_H
