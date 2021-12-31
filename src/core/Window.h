#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H
#include "../core.h"

namespace BlockWorld {

constexpr int DEFAULT_WIDTH = 1280;
constexpr int DEFAULT_HEIGHT = 720;

struct WindowSize {
  int width{DEFAULT_WIDTH};
  int height{DEFAULT_HEIGHT};
};

// struct Destroy_GLFWwindow {
//   void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
// };

// using Smart_GLFWwindow = std::unique_ptr<GLFWwindow, Destroy_GLFWwindow>;

class Window {
 public:
  Window();
  explicit Window(const char* title) noexcept;
  explicit Window(const char* title, WindowSize size,
                  bool fullScreenMode = false) noexcept;
  ~Window();

  //  static auto createWindow(const std::string& title) ->
  //  std::shared_ptr<Window>; static auto createWindow(WindowSize size, const
  //  std::string& title,
  //                           bool fullScreenMode = false)
  //      -> std::shared_ptr<Window>;

  [[nodiscard("tidy told me to")]] auto shouldClose() const noexcept -> bool;
  void close() noexcept;
  [[nodiscard("tidy told me to")]] auto width() const noexcept -> int {
    return _size.width;
  }
  [[nodiscard("tidy told me to")]] auto height() const noexcept -> int {
    return _size.height;
  }
  [[nodiscard("tidy told me to")]] auto nativeWindow() const noexcept
      -> GLFWwindow* {
    return ptr;
  }

  void onResize(int width, int height);

  // Copy: not supported
  Window(const Window& other) = delete;          // copy constructor
  auto operator=(const Window& other) = delete;  // copy assignment
  // Move
  Window(Window&& other) noexcept
      : _size(other._size),
        ptr(std::exchange(other.ptr, nullptr)){};  // move constructor
  auto operator=(Window&& other) noexcept -> Window& {
    _size = other._size;
    std::swap(ptr, other.ptr);
    return *this;
  }

 private:
  GLFWwindow* ptr;
  // Smart_GLFWwindow _nativeWindow;
  WindowSize _size{};
};

}  // namespace BlockWorld

#endif