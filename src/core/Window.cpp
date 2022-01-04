#include "Window.h"

#include <utility>

#include "Input.h"

namespace BlockWorld {

void window_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "window_size_callback " << width << ", " << height << std::endl;
  void* ptr = glfwGetWindowUserPointer(window);
  auto* self = static_cast<Window*>(ptr);
  self->onResize(width, height);
}

Window::Window() : Window("OpenGL Window", WindowSize{}, false) {}
Window::Window(const char* title) noexcept
    : Window(title, WindowSize{}, false) {}
Window::Window(const char* title, WindowSize size, bool fullScreenMode) noexcept
    : _size(size) {
  // Highest OpenGL version Mac supports is 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required for mac
#endif

  // Is primaryMonitor leaking memory?
  GLFWmonitor* primaryMonitor =
      fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
  GLFWwindow* nativeWindow =
      glfwCreateWindow(size.width, size.height, title, primaryMonitor, nullptr);
  ptr = nativeWindow;

  if (nativeWindow == nullptr) {
    std::cerr << "Failed to create GLFW window\n" << std::endl;
    return;
  }

  glfwSetKeyCallback(nativeWindow, Input::keyCallback);
  glfwSetCursorPosCallback(nativeWindow, Input::mouseCallback);
  glfwSetMouseButtonCallback(nativeWindow, Input::mouseButtonCallback);
  glfwMakeContextCurrent(nativeWindow);

#ifndef __EMSCRIPTEN__
  auto loader = gladLoadGLLoader(
      (GLADloadproc)  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
      glfwGetProcAddress);
  if (loader == 0) {
    std::cerr << "Failed to initialize GLAD." << std::endl;
    return;
  }
#endif
  // Handle window resize
  glfwSetWindowUserPointer(nativeWindow, this);
  glfwSetWindowSizeCallback(nativeWindow, window_size_callback);
}

Window::~Window() {
  if (ptr != nullptr) {
    close();
    glfwDestroyWindow(ptr);
    ptr = nullptr;
  }
};

void Window::onResize(
    int width, int height) {  // NOLINT(bugprone-easily-swappable-parameters)
  this->_size.width = width;
  this->_size.height = height;
  glViewport(0, 0, width, height);
}

auto Window::shouldClose() const noexcept -> bool {
  return glfwWindowShouldClose(ptr) == GLFW_TRUE;
}

void Window::close() noexcept { glfwSetWindowShouldClose(ptr, GLFW_TRUE); }

}  // namespace BlockWorld
