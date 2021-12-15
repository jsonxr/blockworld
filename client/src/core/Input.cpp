#include "core/Input.h"

namespace block_world::input {

std::array<bool, GLFW_KEY_LAST> key_pressed_data{};
std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_button_pressed_data{};
float mouse_x = 0.0F;
float mouse_y = 0.0F;
float mouse_scroll_x = 0.0F;
float mouse_scroll_y = 0.0F;

void keyCallback(GLFWwindow * /*window*/, int key, int /*scancode*/, int action,
                 int /*mods*/) {
  if (key >= 0 && key < GLFW_KEY_LAST) {
    std::cout << "Key pressed" << action << std::endl;
    key_pressed_data.at(key) = action == GLFW_PRESS;
  }
}

void mouseCallback(GLFWwindow * /*window*/, double xPos, double yPos) {
  mouse_x = static_cast<float>(xPos);
  mouse_y = static_cast<float>(yPos);
}

void mouseButtonCallback(GLFWwindow * /*window*/, int button, int action,
                         int /*mods*/) {
  if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
    mouse_button_pressed_data.at(button) = action == GLFW_PRESS;
  }
}

void mouseScrollCallback(GLFWwindow * /*window*/, double xOffset,
                         double yOffset) {
  mouse_scroll_x = static_cast<float>(xOffset);
  mouse_scroll_y = static_cast<float>(yOffset);
}

auto isKeyDown(int key) -> bool {
  if (key >= 0 && key < GLFW_KEY_LAST) {
    return key_pressed_data.at(key);
  }

  return false;
}

auto isMouseButtonDown(int mouseButton) -> bool {
  if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST) {
    return mouse_button_pressed_data.at(mouseButton);
  }

  return false;
}

}  // namespace block_world::input