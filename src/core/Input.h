#ifndef MINECRAFT_INPUT_H
#define MINECRAFT_INPUT_H
#include "../core.h"

namespace Minecraft::Input {

extern std::array<bool, GLFW_KEY_LAST> keyPressedData;
extern std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouseButtonPressedData;
extern float mouseX;
extern float mouseY;
extern float mouseScrollX;
extern float mouseScrollY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

bool isKeyDown(int key);
bool isMouseButtonDown(int mouseButton);

}  // namespace Minecraft::Input

#endif