#include "core.h"
#include "core/Window.h"
#include "core/webgl/WebGLRenderer.h"

using namespace BlockWorld;

constexpr auto windowTitle = "BlockWorld";

int exitWithError(const char* msg) {  // NOLINT
  std::cerr << msg << std::endl;
  glfwTerminate();
  std::cerr << "goodbye" << std::endl;
  return EXIT_FAILURE;
}

static void error_callback(int error, const char* description) {
  std::cerr << "Error: " << error << "\n" << description << std::endl;
}

// static void key_callback(GLFWwindow* window, int key, int scancode, int
// action,
//                          int mods) {
//   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//     glfwSetWindowShouldClose(window, GLFW_TRUE);
//   }
//   if (key == GLFW_KEY_E && action == GLFW_PRESS) {
//     std::cerr << "You pressed the e key" << std::endl;
//   }
// }

std::function<void()> loop;
void main_loop() { loop(); }

auto main() -> int {
  glfwSetErrorCallback(error_callback);
  if (glfwInit() == 0) {
    return EXIT_FAILURE;
  }

  std::shared_ptr<Window> window = Window::createWindow(windowTitle);

  if (window == nullptr) {
    return exitWithError("Failed to create GLFW window\n");
  }
  std::unique_ptr<WebGLRenderer> renderer =
      std::make_unique<WebGLRenderer>(window);

  loop = [&] {
    renderer->render();
    glfwPollEvents();
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, true);
#else
  while (!window->shouldClose()) {
    main_loop();
  }
#endif

  window->close();

  glfwTerminate();
  exit(EXIT_SUCCESS);
}