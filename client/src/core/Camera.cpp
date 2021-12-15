#include "core/Camera.h"

namespace block_world {

constexpr float kFullRotation = 360.F;

Camera::Camera(const CameraOptions options) : options_(options) {
  update_camera_vectors();
}

auto Camera::get_view_matrix() const -> mat4 {
  // Fly Around the center...
  //  const float radius = 10.0F;
  //  double camX = sin(glfwGetTime()) * radius;
  //  double camZ = cos(glfwGetTime()) * radius;
  //  return glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0),
  //                          glm::vec3(0.0, 1.0, 0.0));

  return glm::lookAt(options_.position, options_.position + front_,
                     options_.up);
}

auto Camera::get_projection_matrix() const -> mat4 {
  return glm::perspective(glm::radians(options_.zoom),
                          options_.width / options_.height, options_.near,
                          options_.far);
}

// processes input received from any keyboard-like input system. Accepts input
// parameter in the form of camera defined ENUM (to abstract it from windowing
// systems)
void Camera::process_keyboard(const CameraMovement direction,
                              const double deltaTime) {
  float velocity = options_.speed * static_cast<float>(deltaTime);
  if (direction == CameraMovement::kForward) {
    options_.position += front_ * velocity;
  }
  if (direction == CameraMovement::kBackward) {
    options_.position -= front_ * velocity;
  }
  if (direction == CameraMovement::kLeft) {
    options_.position -= right_ * velocity;
  }
  if (direction == CameraMovement::kRight) {
    options_.position += right_ * velocity;
  }
}

// processes input received from a mouse input system. Expects the offset
// value in both the x and y direction.
void Camera::process_mouse_movement(const float xPos, const float yPos,
                                    const bool constrainPitch) {
  if (!mouse_moved_) {
    lastX_ = xPos;
    lastY_ = yPos;
    mouse_moved_ = true;
    return;
  }

  float x_offset = xPos - lastX_;
  float y_offset = lastY_ - yPos;
  lastX_ = xPos;
  lastY_ = yPos;

  auto yaw = options_.yaw + (x_offset * options_.sensitivity);
  auto pitch = options_.pitch + (y_offset * options_.sensitivity);

  std::cout << xPos << "," << yPos << " pitch=" << options_.pitch << "->"
            << pitch << " yaw=" << options_.yaw << "->" << yaw << std::endl;

  //  options_.yaw += yaw;      //(x_offfset * options_.sensitivity);

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (pitch > kPitchUp) {
      std::cout << "pitch up..." << pitch << std::endl;
      pitch = kPitchUp;
    }
    if (pitch < kPitchDown) {
      std::cout << "pitch down..." << pitch << std::endl;
      pitch = kPitchDown;
    }
  }
  if (yaw > kFullRotation) {
    yaw = 0;
  }
  if (yaw < 0) {
    yaw = kFullRotation;
  }

  options_.pitch = pitch;  //(yOffset * options_.sensitivity);
  options_.yaw = yaw;

  // update Front, Right and Up Vectors using the updated Euler angles
  update_camera_vectors();
}

// processes input received from a mouse scroll-wheel event. Only requires
// input on the vertical wheel-axis
void Camera::process_mouse_scroll(const float yOffset) {
  options_.zoom -= yOffset;
  if (options_.zoom < kZoomMin) {
    options_.zoom = kZoomMin;
  }
  if (options_.zoom > kZoomMax) {
    options_.zoom = kZoomMax;
  }
}

void Camera::update_camera_vectors() {
  // calculate the new Front vector
  vec3 front;
  front[0] =
      cos(glm::radians(options_.yaw)) * cos(glm::radians(options_.pitch));
  front[1] = sin(glm::radians(options_.pitch));
  front[2] =
      sin(glm::radians(options_.yaw)) * cos(glm::radians(options_.pitch));
  front_ = glm::normalize(front);
  // also re-calculate the Right and Up vector
  // normalize the vectors, because their length gets
  // closer to 0 the more you look up or down which
  // results in slower movement.
  right_ = glm::normalize(glm::cross(front_, options_.worldUp));
  options_.up = glm::normalize(glm::cross(right_, front_));
}

}  // namespace block_world