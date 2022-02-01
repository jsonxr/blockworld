#include "core/Input.h"

#include "core/Window.h"

namespace app {

void Input::key_callback(int key, int /*scancode*/, int action, int /*mods*/) {
  if (key >= 0 && key < GLFW_KEY_LAST) {
    std::cout << "Key pressed" << action << std::endl;
    key_pressed_data_.at(key) = action == GLFW_PRESS;
  }
}

void Input::mouse_callback(double xPos, double yPos) {
  x_pos_ = static_cast<int>(xPos);
  y_pos_ = static_cast<int>(yPos);

  if (firstMouse_) {
    lastMouseX_ = x_pos_;
    lastMouseY_ = y_pos_;
    firstMouse_ = false;
  }

  deltaMouseX_ = x_pos_ - lastMouseX_;
  deltaMouseY_ = lastMouseY_ - y_pos_;
  lastMouseX_ = x_pos_;
  lastMouseY_ = y_pos_;
}

void Input::mouse_button_callback(int button, int action, int /*mods*/) {
  if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
    mouse_button_pressed_data_.at(button) = action == GLFW_PRESS;
  }
}

void Input::process(Camera &camera, double /*deltaTime*/) {
  float mx = sensitivity_ * static_cast<float>(deltaMouseX_);
  float my = sensitivity_ * static_cast<float>(deltaMouseY_);

  camera.orientation().x += my;
  camera.orientation().y += mx;

  if (camera.orientation().x > 90.0F) camera.orientation().x = 90.0F;
  if (camera.orientation().x < -90.0F) camera.orientation().x = -90.0F;

  const float player_speed = 0.2F;
  if (Input::isKeyPressed(GLFW_KEY_W)) {
    camera.position() += camera.forward() * player_speed;
  } else if (Input::isKeyPressed(GLFW_KEY_S)) {
    camera.position() -= camera.forward() * player_speed;
  }

  if (Input::isKeyPressed(GLFW_KEY_A)) {
    glm::vec3 local_right = glm::cross(camera.forward(), glm::vec3(0, 1, 0));
    camera.position() -= local_right * player_speed;
  } else if (Input::isKeyPressed(GLFW_KEY_D)) {
    glm::vec3 local_right = glm::cross(camera.forward(), glm::vec3(0, 1, 0));
    camera.position() += local_right * player_speed;
  }

  deltaMouseX_ = 0;
  deltaMouseY_ = 0;
}

}  // namespace app

// namespace app::input {

// std::array<bool, GLFW_KEY_LAST> key_pressed_data{};
// std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_button_pressed_data{};

// int mouse_x = 0;
// int mouse_y = 0;
// int delta_mouse_x = 0;
// int delta_mouse_y = 0;

// float mouse_x = 0.0F;
// float mouse_y = 0.0F;
// float mouse_scroll_x = 0.0F;
// float mouse_scroll_y = 0.0F;

// void keyCallback(GLFWwindow * /*window*/, int key, int /*scancode*/, int
// action,
//                  int /*mods*/) {
//   if (key >= 0 && key < GLFW_KEY_LAST) {
//     std::cout << "Key pressed" << action << std::endl;
//     key_pressed_data.at(key) = action == GLFW_PRESS;
//   }
// }

// void mouseCallback(GLFWwindow * /*window*/, double xPos, double yPos) {
//   mouse_x = static_cast<float>(xPos);
//   mouse_y = static_cast<float>(yPos);
// }

// void mouseButtonCallback(GLFWwindow * /*window*/, int button, int action,
//                          int /*mods*/) {
//   if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
//     mouse_button_pressed_data.at(button) = action == GLFW_PRESS;
//   }
// }

// void mouseScrollCallback(GLFWwindow * /*window*/, double xOffset,
//                          double yOffset) {
//   mouse_scroll_x = static_cast<float>(xOffset);
//   mouse_scroll_y = static_cast<float>(yOffset);
// }

// auto isKeyDown(int key) -> bool {
//   if (key >= 0 && key < GLFW_KEY_LAST) {
//     return key_pressed_data.at(key);
//   }

//   return false;
// }

// auto isMouseButtonDown(int mouseButton) -> bool {
//   if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST) {
//     return mouse_button_pressed_data.at(mouseButton);
//   }

//   return false;
// }

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

// }  // namespace app::input