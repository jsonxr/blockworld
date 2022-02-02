#include "Camera.h"

#include "../vendor/glm.h"
#include "Logger.h"

namespace app {

static Logger log{"Camera.cpp"};

Camera::Camera(const CameraOptions options) : options_{options} {}

auto Camera::get_view_matrix() -> mat4 {
  auto pos = options_.position;
  auto yaw = options_.yaw;
  auto pitch = options_.pitch;

  vec3 look_at = vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
                      sin(glm::radians(pitch)),
                      sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
  look_at = glm::normalize((look_at));

//  glm::vec3 direction;
//  direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
//  direction.y = sin(glm::radians(pitch));
//  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  forward_ = vec3(cos(glm::radians(yaw)),
                  0,
                  sin(glm::radians(yaw))
                  );
  forward_ = glm::normalize(forward_);

  vec3 local_right = glm::cross(look_at, vec3(0, 1, 0));
  vec3 local_up = glm::cross(local_right, look_at);
  auto view_matrix = glm::lookAt(pos, pos + look_at, local_up);
  return view_matrix;
}

auto Camera::get_projection_matrix() const -> mat4 {
  auto projection_matrix = glm::perspective(
      glm::radians(options_.fov), options_.aspect, options_.near, options_.far);
  return projection_matrix;
}

}  // namespace app