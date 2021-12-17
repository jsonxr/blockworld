#include "Window.h"

#include <utility>

#include "Input.h"

namespace BlockWorld {

constexpr int DEFAULT_WIDTH = 1280;
constexpr int DEFAULT_HEIGHT = 720;

Window::Window() = default;

Window::Window(int width,   // NOLINT(bugprone-easily-swappable-parameters)
               int height)  // NOLINT(bugprone-easily-swappable-parameters)
    : _width(width), _height(height) {}

void window_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "window_size_callback " << width << ", " << height << std::endl;
  void* ptr = glfwGetWindowUserPointer(window);
  auto* self = static_cast<Window*>(ptr);
  self->onResize(width, height);
}
void Window::onResize(
    int width, int height) {  // NOLINT(bugprone-easily-swappable-parameters)
  this->_width = width;
  this->_height = height;
}

auto Window::createWindow(const std::string& title) -> std::shared_ptr<Window> {
  return createWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, title, false);
}

auto Window::createWindow(int width, int height, const std::string& title,
                          bool fullScreenMode) -> std::shared_ptr<Window> {
  // Highest OpenGL version Mac supports is 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required for mac

  // Only supply the monitor if we want to start the window in full-screen
  // mode
  std::shared_ptr<Window> res = std::make_unique<Window>(width, height);

  GLFWmonitor* primaryMonitor =
      fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
  Smart_GLFWwindow nativeWindow;

  res->_nativeWindow.reset(
      glfwCreateWindow(width, height, title.c_str(), primaryMonitor, nullptr));
  if (res->_nativeWindow == nullptr) {
    std::cerr << "Failed to create GLFW window\n" << std::endl;
    glfwTerminate();
    return nullptr;
  }

  glfwSetKeyCallback(res->_nativeWindow.get(), Input::keyCallback);
  glfwSetCursorPosCallback(res->_nativeWindow.get(), Input::mouseCallback);
  glfwSetMouseButtonCallback(res->_nativeWindow.get(),
                             Input::mouseButtonCallback);
  glfwMakeContextCurrent(res->_nativeWindow.get());

#ifndef __EMSCRIPTEN__
  if (gladLoadGLLoader(
          (GLADloadproc)
              glfwGetProcAddress) ==  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
      0) {
    std::cerr << "Failed to initialize GLAD." << std::endl;
    return nullptr;
  }
#endif
  // Handle window resize
  glfwSetWindowUserPointer(res->_nativeWindow.get(), res.get());
  glfwSetWindowSizeCallback(res->_nativeWindow.get(), window_size_callback);
  return res;
}

auto Window::shouldClose() -> bool {
  return glfwWindowShouldClose(_nativeWindow.get()) == GLFW_TRUE;
}

void Window::close() {
  glfwSetWindowShouldClose(_nativeWindow.get(), GLFW_TRUE);
}

}  // namespace BlockWorld
