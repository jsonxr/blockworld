#ifndef BLOCK_WORLD_CAMERA_H
#define BLOCK_WORLD_CAMERA_H

#include <glm/ext.hpp>

#include "Window.h"

namespace BlockWorld {

constexpr float YAW = 270.0F;
constexpr float PITCH = 0.0F;
constexpr float PITCH_UP = 90.F;
constexpr float PITCH_DOWN = -90.F;
constexpr float SPEED = 2.5F;
constexpr float SENSITIVITY = 0.1F;
constexpr float ZOOM = 45.0F;
constexpr float ZOOM_MIN = 1.0F;
constexpr float ZOOM_MAX = 45.0F;

constexpr vec3 POSITION = vec3(0.0F, 0.0F, 0.0F);
constexpr vec3 WORLD_UP = vec3(0.0F, 1.0F, 0.0F);
constexpr vec3 FRONT = glm::vec3(0.0F, 0.0F, -1.0F);

enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };
struct CameraOptions {
  vec3 position = POSITION;
  vec3 up = WORLD_UP;
  vec3 worldUp = WORLD_UP;
  float yaw = {YAW};
  float pitch{PITCH};
  float speed{SPEED};
  float sensitivity{SENSITIVITY};
  float zoom{ZOOM};
  float width{DEFAULT_WIDTH};
  float height{DEFAULT_HEIGHT};
  float near{0.1F};
  float far{100.F};
};

class Camera {
 public:
  Camera() = default;
  explicit Camera(CameraOptions options);
  auto get_view_matrix() -> mat4;
  auto get_projection_matrix() -> mat4;
  void process_keyboard(CameraMovement direction, double deltaTime);
  void process_mouse_movement(float xPos, float yPos,
                              bool constrainPitch = true);
  void process_mouse_scroll(float yOffset);

 private:
  CameraOptions _options{};
  vec3 _front = FRONT;
  vec3 _right{};
  bool _mouse_moved{true};
  float _lastX{0 / 2.0};
  float _lastY{0 / 2.0};

  // calculates the front vector from the Camera's (updated) Euler Angles
  void update_camera_vectors();
};

}  // namespace BlockWorld

#endif  // BLOCK_WORLD_CAMERA_H
