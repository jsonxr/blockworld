#ifndef APP_CAMERA_H
#define APP_CAMERA_H

#include "../vendor/glm.h"

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
  vec3 position{0.0, 258.6, 50};
  float yaw{270.0};
  float pitch{0};

  float fov{45.0};
  float near{0.1F};
  float far{100.0F};
  float aspect{1920.F / 1080.F};  // width/height of window
};

class Camera {
 public:
  Camera() = default;
  explicit Camera(CameraOptions options);

  [[nodiscard]] auto get_view_matrix() -> mat4;
  [[nodiscard]] auto get_projection_matrix() const -> mat4;

  void set_aspect(float aspect) { options_.aspect = aspect; }
  void set_fov(float fov) { options_.fov = fov; }
  void set_pitch(float pitch) {
    options_.pitch = pitch;
    if (options_.pitch > 89.9) options_.pitch = 89.9;
    if (options_.pitch < -89.9) options_.pitch = -89.9;
  }
  void set_position(const vec3 &pos) { options_.position = pos; }
  void set_yaw(float yaw) {
    options_.yaw = yaw;
    if (options_.yaw > 360) options_.yaw = 0;
    if (options_.yaw < 0) options_.yaw = 360;
  }

  auto aspect() const -> const float & { return options_.aspect; }
  auto forward() const -> const vec3 & { return forward_; }
  auto fov() const -> const float & { return options_.fov; }
  auto pitch() const -> const float & { return options_.pitch; }
  auto position() const -> const vec3 & { return options_.position; }
  auto yaw() const -> const float & { return options_.yaw; }

 private:
  CameraOptions options_{};
  glm::mat4x4 view_matrix_{};
  glm::mat4x4 projection_matrix_{};
  glm::vec3 forward_{};
};

}  // namespace app

#endif  // APP_CAMERA_H
