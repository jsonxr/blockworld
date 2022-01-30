#ifndef MINECRAFT_INPUT_H
#define MINECRAFT_INPUT_H
#include "../core.h"
#include "core/Camera.h"

namespace block_world {

class Input {
 public:
  void process(Camera &camera, double deltaTime);

  void key_callback(int key, int scancode, int action, int mods);
  void mouse_callback(double xPos, double yPos);
  void mouse_button_callback(int button, int action, int mods);

  auto isKeyPressed(int key) -> bool { return key_pressed_data_[key]; }

 private:
  float sensitivity_{0.1};
  int lastMouseX_{0};
  int lastMouseY_{0};
  int deltaMouseX_{0};
  int deltaMouseY_{0};
  bool firstMouse_{true};

  int x_pos_{0};
  int y_pos_{0};
  std::array<bool, GLFW_KEY_LAST> key_pressed_data_{};
  std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_button_pressed_data_{};
};

// namespace block_world

// extern std::array<bool, GLFW_KEY_LAST> key_pressed_data;
// extern std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_button_pressed_data;
// extern float mouse_x;
// extern float mouse_y;
// extern float mouse_scroll_x;
// extern float mouse_scroll_y;

// void keyCallback(GLFWwindow *window, int key, int scancode, int action,
//                  int mods);
// void mouseCallback(GLFWwindow *window, double xPos, double yPos);
// void mouseButtonCallback(GLFWwindow *window, int button, int action, int
// mods); void mouseScrollCallback(GLFWwindow *window, double xOffset, double
// yOffset);

// auto isKeyDown(int key) -> bool;
// auto isMouseButtonDown(int mouseButton) -> bool;

}  // namespace block_world

#endif