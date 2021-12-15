#include "Window.h"

#include "Input.h"

namespace BlockWorld {

Window::Window(int windowWidth, int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {}

std::unique_ptr<Window> Window::createWindow(int width, int height,
                                             std::string title,
                                             bool fullScreenMode) {
  // Highest OpenGL version Mac supports is 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);  // Required for mac

  // Only supply the monitor if we want to start the window in full-screen mode
  std::unique_ptr<Window> res = std::make_unique<Window>(width, height);
  GLFWmonitor* primaryMonitor =
      fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
  Smart_GLFWwindow nativeWindow;
  res->nativeWindow.reset(
      glfwCreateWindow(width, height, title.c_str(), primaryMonitor, nullptr));

  if (res->nativeWindow == nullptr) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return nullptr;
  }

  glfwSetKeyCallback(res->nativeWindow.get(), Input::keyCallback);
  glfwSetCursorPosCallback(res->nativeWindow.get(), Input::mouseCallback);
  glfwSetMouseButtonCallback(res->nativeWindow.get(),
                             Input::mouseButtonCallback);
  glfwMakeContextCurrent(res->nativeWindow.get());

#ifndef __EMSCRIPTEN__
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD." << std::endl;
    return nullptr;
  }
#endif

  // Make sure not to call any OpenGL functions until *after* we initialize our
  // function loader
  glfwSwapInterval(1);
  return res;
}

bool Window::shouldClose() { return glfwWindowShouldClose(nativeWindow.get()); }

void Window::close() {
  glfwSetWindowShouldClose(nativeWindow.get(), GLFW_TRUE);
}

}  // namespace BlockWorld

//
// void Window::installMainCallbacks() {
//  if (nativeWindow != nullptr) {
//    glfwSetKeyCallback(nativeWindow, Input::keyCallback);
//    glfwSetCursorPosCallback(nativeWindow, Input::mouseCallback);
//    glfwSetMouseButtonCallback(nativeWindow, Input::mouseButtonCallback);
//  }
//}
//
// void Window::close() {
//  if (nativeWindow != nullptr) {
//    glfwSetWindowShouldClose(nativeWindow, GLFW_TRUE);
//  }
//}
//
// std::unique_ptr<Window> Window::createWindow(int width, int height,
//                                             const char* title,
//                                             bool fullScreenMode) {
//  // Highest OpenGL version Mac supports is 4.1
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);  // Required for mac
//
//  // Only supply the monitor if we want to start the window in full-screen
//  mode std::unique_ptr<Window> res = std::make_unique<Window>(width, height);
//  GLFWmonitor* primaryMonitor =
//      fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
//  res->nativeWindow =
//      glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
//  if (res->nativeWindow == nullptr) {
//    printf("Failed to create GLFW window\n");
//    glfwTerminate();
//    return nullptr;
//  }
//  glfwMakeContextCurrent(res->nativeWindow);
//
//  return res;
//}
//
// void Window::freeWindow(std::unique_ptr<Window> window) {
//  if (window) {
//    glfwDestroyWindow(window->nativeWindow);
//    delete window;
//  }
//}
//
// Window::Window(int windowWidth, int windowHeight)
//    : windowWidth(windowWidth), windowHeight(windowHeight) {}
//}  // namespace BlockWorld