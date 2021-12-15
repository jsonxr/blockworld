#ifndef MINECRAFT_WINDOW_H
#define MINECRAFT_WINDOW_H
#include "core.h"

namespace block_world {

constexpr int kDefaultWindowWidth = 1280;
constexpr int kDefaultWindowHeight = 720;

struct WindowSize {
  int width{kDefaultWindowWidth};
  int height{kDefaultWindowHeight};
};

// struct Destroy_GLFWwindow {
//   void operator()(GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
// };

// using Smart_GLFWwindow = std::unique_ptr<GLFWwindow, Destroy_GLFWwindow>;

class Window {
 public:
  Window();
  explicit Window(const char *title) noexcept;
  explicit Window(const char *title, WindowSize size,
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
    return size_.width;
  }
  [[nodiscard("tidy told me to")]] auto height() const noexcept -> int {
    return size_.height;
  }
  [[nodiscard("tidy told me to")]] auto nativeWindow() const noexcept
      -> GLFWwindow * {
    return ptr_;
  }

  void onResize(int width, int height);

  // Copy: not supported
  Window(const Window &other) = delete;          // copy constructor
  auto operator=(const Window &other) = delete;  // copy assignment
  // Move
  Window(Window &&other) noexcept
      : size_(other.size_),
        ptr_(std::exchange(other.ptr_, nullptr)){};  // move constructor
  auto operator=(Window &&other) noexcept -> Window & {
    size_ = other.size_;
    std::swap(ptr_, other.ptr_);
    return *this;
  }

 private:
  GLFWwindow *ptr_;
  // Smart_GLFWwindow _nativeWindow;
  WindowSize size_{};
};

}  // namespace block_world

#endif