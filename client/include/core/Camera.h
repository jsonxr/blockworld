#ifndef APP_CAMERA_H
#define APP_CAMERA_H

#include "vendor/glm.h"

namespace app {

constexpr float kYaw = 270.0F;
constexpr float kPitch = 0.0F;
constexpr float kPitchUp = 90.F;
constexpr float kPitchDown = -90.F;
constexpr float kSpeed = 2.5F;
constexpr float kSensitivity = 0.1F;
constexpr float kZoom = 45.0F;
constexpr float kZoomMin = 1.0F;
constexpr float kZoomMax = 45.0F;
constexpr float kCameraNear = 0.1F;
constexpr float kCameraFar = 100.0F;

constexpr vec3 kPosition = vec3(0.0F, 0.0F, 0.0F);
constexpr vec3 kWorldUp = vec3(0.0F, 1.0F, 0.0F);
constexpr vec3 kFront = glm::vec3(0.0F, 0.0F, -1.0F);

enum class CameraMovement { kForward, kBackward, kLeft, kRight };
struct CameraOptions {
  vec3 position{0.0, 1.6, 5.0};
  vec3 orientation{0.0, 0.0, 0.0};

  float fov{45.0};
  float near{0.1F};
  float far{100.0F};
  float aspect{1920.F / 1080.F};  // width/height of window
  // vec3 up = kWorldUp;
  // vec3 worldUp = kWorldUp;
  // float yaw = {kYaw};
  // float pitch{kPitch};
  // float speed{kSpeed};
  // float sensitivity{kSensitivity};
  // float zoom{kZoom};
  // float width{kDefaultWindowWidth};
  // float height{kDefaultWindowHeight};
};

class Camera {
 public:
  Camera() = default;
  explicit Camera(CameraOptions options);

  [[nodiscard]] auto get_view_matrix() -> mat4;
  [[nodiscard]] auto get_projection_matrix() const -> mat4;

  void set_aspect(float aspect) { options_.aspect = aspect; }
  void set_position(const vec3 &pos) { options_.position = pos; }
  void set_fov(float fov) { options_.fov = fov; }
  void set_orientation(const vec3 &orientation) {}

  auto orientation() -> vec3 & { return options_.orientation; }
  auto position() -> vec3 & { return options_.position; }
  auto forward() -> const vec3 & { return forward_; }

 private:
  glm::vec3 forward_{};
  CameraOptions options_{};
  glm::mat4x4 view_matrix_{};
  glm::mat4x4 projection_matrix_{};

  // calculates the front vector from the Camera's (updated) Euler Angles
  void update_camera_vectors() const;
};

}  // namespace app

#endif  // APP_CAMERA_H
