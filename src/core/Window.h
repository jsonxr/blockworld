#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H
#include "../core.h"

namespace BlockWorld {

struct Destroy_GLFWwindow {
  void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
};

using Smart_GLFWwindow = std::unique_ptr<GLFWwindow, Destroy_GLFWwindow>;

class Window {
 public:
  Window();
  Window(int windowWidth, int windowHeight);
  static auto createWindow(const std::string& title) -> std::shared_ptr<Window>;
  static auto createWindow(int width, int height, const std::string& title,
                           bool fullScreenMode = false)
      -> std::shared_ptr<Window>;
  auto shouldClose() -> bool;
  void close();
  [[nodiscard]] auto width() const -> int { return _width; }
  [[nodiscard]] auto height() const -> int { return _height; }
  auto nativeWindow() -> GLFWwindow* { return _nativeWindow.get(); }

  void onResize(int width, int height);

 private:
  Smart_GLFWwindow _nativeWindow;
  int _width{};
  int _height{};
};

}  // namespace BlockWorld

#endif