#include "Camera.h"

#include "../vendor/glm.h"

namespace app {

constexpr float kUp = 89.9999;

Camera::Camera(const CameraOptions options) : options_{options} {}

// auto Camera::options() -> CameraOptions & { return options_; }
void Camera::set_options(CameraOptions options) {
  options_ = options;
  // pitch
  if (options_.pitch > kUp) options_.pitch = kUp;
  if (options_.pitch < -kUp) options_.pitch = -kUp;
  // yaw
  if (options_.yaw > 360) options_.yaw = 0;
  if (options_.yaw < 0) options_.yaw = 360;

  calculateMatrices();
}
auto Camera::options() const -> const CameraOptions & { return options_; }
auto Camera::forward() const -> const vec3 & { return forward_; }
auto Camera::position() const -> const vec3 & { return options_.pos; }
auto Camera::view_matrix() const -> const mat4 & { return view_; }
auto Camera::projection_matrix() const -> const mat4 & { return projection_; }

void Camera::calculateMatrices() {
  // forward vector
  forward_ = glm::normalize(vec3(cos(glm::radians(options_.yaw)), 0,
                                 sin(glm::radians(options_.yaw))));

  // projection matrix
  projection_ = glm::perspective(glm::radians(options_.fov), options_.aspect,
                                 options_.near, options_.far);

  // view matrix
  vec3 look_at = glm::normalize(vec3(
      cos(glm::radians(options_.pitch)) * cos(glm::radians(options_.yaw)),
      sin(glm::radians(options_.pitch)),
      sin(glm::radians(options_.yaw)) * cos(glm::radians(options_.pitch))));
  vec3 local_right = glm::cross(look_at, vec3(0, 1, 0));
  vec3 local_up = glm::cross(local_right, look_at);
  view_ = glm::lookAt(options_.pos, options_.pos + look_at, local_up);
}

}  // namespace app