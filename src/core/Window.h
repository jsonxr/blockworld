#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H
#include "../core.h"

namespace BlockWorld {

struct Destroy_GLFWwindow {
  void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
};

typedef std::unique_ptr<GLFWwindow, Destroy_GLFWwindow> Smart_GLFWwindow;

class Window {
 public:
  Smart_GLFWwindow nativeWindow;
  Window(int windowWidth, int windowHeight);
  static std::unique_ptr<Window> createWindow(int width, int height,
                                              std::string title,
                                              bool fullScreenMode = false);
  bool shouldClose();
  void close();

 private:
  int windowWidth{0};
  int windowHeight{0};
};

}  // namespace BlockWorld

#endif