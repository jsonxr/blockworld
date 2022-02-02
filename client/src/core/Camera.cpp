#include "core/Camera.h"

#include "core/Logger.h"
#include "vendor/glm.h"

namespace app {

static Logger log{"Camera.cpp"};

Camera::Camera(const CameraOptions options) : options_(options) {}

auto Camera::get_view_matrix() -> mat4 {
  auto pos = options_.position;
  auto yaw = options_.yaw;
  auto pitch = options_.pitch;

  glm::vec3 direction;
  direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  forward_ = glm::normalize(direction);
  vec3 local_right = glm::cross(forward_, vec3(0, 1, 0));
  vec3 local_up = glm::cross(local_right, forward_);

  auto view_matrix = glm::lookAt(pos, pos + forward_, local_up);
  return view_matrix;
}

auto Camera::get_projection_matrix() const -> mat4 {
  auto projection_matrix = glm::perspective(
      glm::radians(options_.fov), options_.aspect, options_.near, options_.far);
  return projection_matrix;
}

// // processes input received from any keyboard-like input system. Accepts
// input
// // parameter in the form of camera defined ENUM (to abstract it from
// windowing
// // systems)
// void Camera::process_keyboard(const CameraMovement direction,
//                               const double deltaTime) {
//   float velocity = options_.speed * static_cast<float>(deltaTime);
//   if (direction == CameraMovement::kForward) {
//     options_.position += front_ * velocity;
//   }
//   if (direction == CameraMovement::kBackward) {
//     options_.position -= front_ * velocity;
//   }
//   if (direction == CameraMovement::kLeft) {
//     options_.position -= right_ * velocity;
//   }
//   if (direction == CameraMovement::kRight) {
//     options_.position += right_ * velocity;
//   }
// }

// // processes input received from a mouse input system. Expects the offset
// // value in both the x and y direction.
// void Camera::process_mouse_movement(const float xPos, const float yPos,
//                                     const bool constrainPitch) {
//   if (!mouse_moved_) {
//     lastX_ = xPos;
//     lastY_ = yPos;
//     mouse_moved_ = true;
//     return;
//   }

//   float x_offset = xPos - lastX_;
//   float y_offset = lastY_ - yPos;
//   lastX_ = xPos;
//   lastY_ = yPos;

//   auto yaw = options_.yaw + (x_offset * options_.sensitivity);
//   auto pitch = options_.pitch + (y_offset * options_.sensitivity);

//   std::cout << xPos << "," << yPos << " pitch=" << options_.pitch << "->"
//             << pitch << " yaw=" << options_.yaw << "->" << yaw << std::endl;

//   //  options_.yaw += yaw;      //(x_offfset * options_.sensitivity);

//   // make sure that when pitch is out of bounds, screen doesn't get flipped
//   if (constrainPitch) {
//     if (pitch > kPitchUp) {
//       std::cout << "pitch up..." << pitch << std::endl;
//       pitch = kPitchUp;
//     }
//     if (pitch < kPitchDown) {
//       std::cout << "pitch down..." << pitch << std::endl;
//       pitch = kPitchDown;
//     }
//   }
//   if (yaw > kFullRotation) {
//     yaw = 0;
//   }
//   if (yaw < 0) {
//     yaw = kFullRotation;
//   }

//   options_.pitch = pitch;  //(yOffset * options_.sensitivity);
//   options_.yaw = yaw;

//   // update Front, Right and Up Vectors using the updated Euler angles
//   update_camera_vectors();
// }

// // processes input received from a mouse scroll-wheel event. Only requires
// // input on the vertical wheel-axis
// void Camera::process_mouse_scroll(const float yOffset) {
//   options_.zoom -= yOffset;
//   if (options_.zoom < kZoomMin) {
//     options_.zoom = kZoomMin;
//   }
//   if (options_.zoom > kZoomMax) {
//     options_.zoom = kZoomMax;
//   }
// }

// void Camera::update_camera_vectors() const {
//   vec3 direction;
//   direction.x = cos(glm::radians(options_.orientation.y)) *
//                 cos(glm::radians(options_.orientation.x));
//   direction.y = sin(glm::radians(options_.orientation.x));
//   direction.z = sin(glm::radians(options_.orientation.y)) *
//                 cos(glm::radians(options_.orientation.x));
//   vec3 forward = glm::normalize(direction);
//   // 0 1 0
//   vec3 local_right = glm::cross(forward, vec3(0, 1, 0));
//   vec3 local_up = glm::cross(local_right, forward);

//   glm::mat4x4 view_matrix =
//       glm::lookAt(options_.position, options_.position + forward, local_up);

//   // // calculate the new Front vector
//   // vec3 front;
//   // front[0] =
//   //     cos(glm::radians(options_.yaw)) * cos(glm::radians(options_.pitch));
//   // front[1] = sin(glm::radians(options_.pitch));
//   // front[2] =
//   //     sin(glm::radians(options_.yaw)) * cos(glm::radians(options_.pitch));
//   // front_ = glm::normalize(front);
//   // // also re-calculate the Right and Up vector
//   // // normalize the vectors, because their length gets
//   // // closer to 0 the more you look up or down which
//   // // results in slower movement.
//   // right_ = glm::normalize(glm::cross(front_, options_.worldUp));
//   // options_.up = glm::normalize(glm::cross(right_, front_));
// }

}  // namespace app