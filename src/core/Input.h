#ifndef MINECRAFT_INPUT_H
#define MINECRAFT_INPUT_H
#include "../core.h"

namespace BlockWorld::Input {

extern std::array<bool, GLFW_KEY_LAST> keyPressedData;
extern std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouseButtonPressedData;
extern float mouseX;
extern float mouseY;
extern float mouseScrollX;
extern float mouseScrollY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

auto isKeyDown(int key) -> bool;
auto isMouseButtonDown(int mouseButton) -> bool;

}  // namespace BlockWorld::Input

#endif