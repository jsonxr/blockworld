#ifndef MINECRAFT_INPUT_H
#define MINECRAFT_INPUT_H
#include "../core.h"

namespace block_world::input {

extern std::array<bool, GLFW_KEY_LAST> key_pressed_data;
extern std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouse_button_pressed_data;
extern float mouse_x;
extern float mouse_y;
extern float mouse_scroll_x;
extern float mouse_scroll_y;

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

auto isKeyDown(int key) -> bool;
auto isMouseButtonDown(int mouseButton) -> bool;

}  // namespace block_world::input

#endif