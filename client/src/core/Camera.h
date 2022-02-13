#ifndef APP_CAMERA_H
#define APP_CAMERA_H

#include "../vendor/glm.h"

namespace app {

/*
            -z  270°
             |
             |
180° -x - - -+- - - +x  0°
             |
             |
            +z  90°
*/

struct CameraOptions {
  vec3 pos{0, 0, 0};
  float yaw{};
  float pitch{};

  float fov{45.0};
  float near{0.1F};
  float far{1000.0F};
  float aspect{1920.F / 1080.F};  // width/height of window
};

class Camera {
 public:
  Camera() = default;
  explicit Camera(CameraOptions options);

  auto view_matrix() const -> const mat4 &;
  auto projection_matrix() const -> const mat4 &;

  void set_options(CameraOptions options);
  auto options() const -> const CameraOptions &;

  auto forward() const -> const vec3 &;
  auto position() const -> const vec3 &;

 private:
  CameraOptions options_{};
  glm::mat4x4 view_{};
  glm::mat4x4 projection_{};
  glm::vec3 forward_{};

  void calculateMatrices();
};

}  // namespace app

#endif  // APP_CAMERA_H
