#include "core/Input.h"

#include "core/Window.h"

namespace app {

void Input::key_callback(int key, int /*scancode*/, int action, int /*mods*/) {
  if (key >= 0 && key < GLFW_KEY_LAST) {
    key_pressed_data_.at(key) = action == GLFW_PRESS || action == GLFW_REPEAT;
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
  // auto orientation = camera.orientation();
  auto yaw = camera.yaw();
  auto pitch = camera.pitch();

  camera.set_yaw(yaw + mx);
  camera.set_pitch(pitch + my);

  const float player_speed = 0.2F;
  if (Input::isKeyPressed(GLFW_KEY_W)) {
    // camera.position() += camera.forward() * player_speed;
    camera.set_position(camera.position() + camera.forward() * player_speed);
  }
  if (Input::isKeyPressed(GLFW_KEY_S)) {
    camera.set_position(camera.position() - camera.forward() * player_speed);
  }
  if (Input::isKeyPressed(GLFW_KEY_A)) {
    glm::vec3 local_right = glm::cross(camera.forward(), glm::vec3(0, 1, 0));
    camera.set_position(camera.position() - local_right * player_speed);
  }
  if (Input::isKeyPressed(GLFW_KEY_D)) {
    glm::vec3 local_right = glm::cross(camera.forward(), glm::vec3(0, 1, 0));
    camera.set_position(camera.position() + local_right * player_speed);
  }

  deltaMouseX_ = 0;
  deltaMouseY_ = 0;
}

}  // namespace app
