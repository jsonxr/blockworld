#include "core/Window.h"

#include <utility>

#include "core/Input.h"

namespace block_world {

void windowsize_callback(GLFWwindow *window, int width, int height) {
  std::cout << "windowsize__callback " << width << ", " << height << std::endl;
  void *ptr = glfwGetWindowUserPointer(window);
  auto *self = static_cast<Window *>(ptr);
  self->onResize(width, height);
}

Window::Window() : Window("OpenGL Window", WindowSize{}, false) {}
Window::Window(const char *title) noexcept
    : Window(title, WindowSize{}, false) {}
Window::Window(const char *title, WindowSize size, bool fullScreenMode) noexcept
    : size_(size) {
  // Highest OpenGL version Mac supports is 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required for mac
#endif

  // Is primaryMonitor leaking memory?
  GLFWmonitor *primary_monitor =
      fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
  GLFWwindow *native_window = glfwCreateWindow(size.width, size.height, title,
                                               primary_monitor, nullptr);
  ptr_ = native_window;

  if (native_window == nullptr) {
    std::cerr << "Failed to create GLFW window\n" << std::endl;
    return;
  }

  glfwSetKeyCallback(native_window, input::keyCallback);
  glfwSetCursorPosCallback(native_window, input::mouseCallback);
  glfwSetMouseButtonCallback(native_window, input::mouseButtonCallback);
  glfwMakeContextCurrent(native_window);

#ifndef __EMSCRIPTEN__
  auto loader =
      gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  if (loader == 0) {
    std::cerr << "Failed to initialize GLAD." << std::endl;
    return;
  }
#endif

  // Handle window resize
  glfwSetWindowUserPointer(native_window, this);
  glfwSetWindowSizeCallback(native_window, windowsize_callback);
}

Window::~Window() {
  if (ptr_ != nullptr) {
    close();
    glfwDestroyWindow(ptr_);
    ptr_ = nullptr;
  }
};

void Window::onResize(
    int width, int height) {  // NOLINT(bugprone-easily-swappable-parameters)
  this->size_.width = width;
  this->size_.height = height;
  glViewport(0, 0, width, height);
}

auto Window::shouldClose() const noexcept -> bool {
  return glfwWindowShouldClose(ptr_) == GLFW_TRUE;
}

void Window::close() noexcept { glfwSetWindowShouldClose(ptr_, GLFW_TRUE); }

}  // namespace block_world
