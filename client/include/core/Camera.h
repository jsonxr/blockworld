#ifndef BLOCK_WORLD_CAMERA_H
#define BLOCK_WORLD_CAMERA_H

#include "Window.h"
#include "vendor/glm.h"

namespace block_world {

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
  vec3 position = kPosition;
  vec3 up = kWorldUp;
  vec3 worldUp = kWorldUp;
  float yaw = {kYaw};
  float pitch{kPitch};
  float speed{kSpeed};
  float sensitivity{kSensitivity};
  float zoom{kZoom};
  float width{kDefaultWindowWidth};
  float height{kDefaultWindowHeight};
  float near{kCameraNear};
  float far{kCameraFar};
};

class Camera {
 public:
  Camera() = default;
  explicit Camera(CameraOptions options);

  [[nodiscard]] auto get_view_matrix() const -> mat4;
  [[nodiscard]] auto get_projection_matrix() const -> mat4;

  void process_keyboard(CameraMovement direction, double deltaTime);
  void process_mouse_movement(float xPos, float yPos,
                              bool constrainPitch = true);
  void process_mouse_scroll(float yOffset);

 private:
  CameraOptions options_{};
  vec3 front_ = kFront;
  vec3 right_{};
  bool mouse_moved_{true};
  float lastX_{};
  float lastY_{};

  // calculates the front vector from the Camera's (updated) Euler Angles
  void update_camera_vectors();
};

}  // namespace block_world

#endif  // BLOCK_WORLD_CAMERA_H
