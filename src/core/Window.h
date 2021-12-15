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
  Window();
  Window(int windowWidth, int windowHeight);
  static std::shared_ptr<Window> createWindow(std::string title);
  static std::shared_ptr<Window> createWindow(int width, int height,
                                              std::string title,
                                              bool fullScreenMode = false);
  bool shouldClose();
  void close();
  int width() const { return _width; }
  int height() const { return _height; }
  GLFWwindow* nativeWindow() { return _nativeWindow.get(); }

 private:
  Smart_GLFWwindow _nativeWindow;
  int _width{};
  int _height{};
};

}  // namespace BlockWorld

#endif