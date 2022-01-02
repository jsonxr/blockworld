#include "Camera.h"

namespace BlockWorld {

Camera::Camera(const CameraOptions options) : _options(options) {
  update_camera_vectors();
}

auto Camera::get_view_matrix() -> mat4 {
  // Fly Around the center...
  //  const float radius = 10.0F;
  //  double camX = sin(glfwGetTime()) * radius;
  //  double camZ = cos(glfwGetTime()) * radius;
  //  return glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0),
  //                          glm::vec3(0.0, 1.0, 0.0));

  return glm::lookAt(_options.position, _options.position + _front,
                     _options.up);
}

auto Camera::get_projection_matrix() -> mat4 {
  return glm::perspective(glm::radians(_options.zoom),
                          _options.width / _options.height, _options.near,
                          _options.far);
}

// processes input received from any keyboard-like input system. Accepts input
// parameter in the form of camera defined ENUM (to abstract it from windowing
// systems)
void Camera::process_keyboard(const CameraMovement direction,
                              const double deltaTime) {
  float velocity = _options.speed * deltaTime;
  if (direction == CameraMovement::FORWARD) {
    _options.position += _front * velocity;
  }
  if (direction == CameraMovement::BACKWARD) {
    _options.position -= _front * velocity;
  }
  if (direction == CameraMovement::LEFT) {
    _options.position -= _right * velocity;
  }
  if (direction == CameraMovement::RIGHT) {
    _options.position += _right * velocity;
  }
}

// processes input received from a mouse input system. Expects the offset
// value in both the x and y direction.
void Camera::process_mouse_movement(const float xPos, const float yPos,
                                    const bool constrainPitch) {
  if (!_mouse_moved) {
    _lastX = xPos;
    _lastY = yPos;
    _mouse_moved = true;
    return;
  }

  float xOffset = xPos - _lastX;
  float yOffset = _lastY - yPos;
  _lastX = xPos;
  _lastY = yPos;

  auto yaw = _options.yaw + (xOffset * _options.sensitivity);
  auto pitch = _options.pitch + (yOffset * _options.sensitivity);

  std::cout << xPos << "," << yPos << " pitch=" << _options.pitch << "->"
            << pitch << " yaw=" << _options.yaw << "->" << yaw << std::endl;

  //  _options.yaw += yaw;      //(xOffset * _options.sensitivity);

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (pitch > PITCH_UP) {
      std::cout << "pitch up..." << pitch << std::endl;
      pitch = PITCH_UP;
    }
    if (pitch < PITCH_DOWN) {
      std::cout << "pitch down..." << pitch << std::endl;
      pitch = PITCH_DOWN;
    }
  }
  if (yaw > 360.0F) {
    yaw = 0;
  }
  if (yaw < 0) {
    yaw = 360.0F;
  }

  _options.pitch = pitch;  //(yOffset * _options.sensitivity);
  _options.yaw = yaw;

  // update Front, Right and Up Vectors using the updated Euler angles
  update_camera_vectors();
}

// processes input received from a mouse scroll-wheel event. Only requires
// input on the vertical wheel-axis
void Camera::process_mouse_scroll(const float yOffset) {
  _options.zoom -= yOffset;
  if (_options.zoom < ZOOM_MIN) {
    _options.zoom = ZOOM_MIN;
  }
  if (_options.zoom > ZOOM_MAX) {
    _options.zoom = ZOOM_MAX;
  }
}

void Camera::update_camera_vectors() {
  // calculate the new Front vector
  vec3 front;
  front[0] =
      cos(glm::radians(_options.yaw)) * cos(glm::radians(_options.pitch));
  front[1] = sin(glm::radians(_options.pitch));
  front[2] =
      sin(glm::radians(_options.yaw)) * cos(glm::radians(_options.pitch));
  _front = glm::normalize(front);
  // also re-calculate the Right and Up vector
  // normalize the vectors, because their length gets
  // closer to 0 the more you look up or down which
  // results in slower movement.
  _right = glm::normalize(glm::cross(_front, _options.worldUp));
  _options.up = glm::normalize(glm::cross(_right, _front));
}

}  // namespace BlockWorld