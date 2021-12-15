#include "core.h"
#include "core/Window.h"

using namespace BlockWorld;

const int windowWidth = 1280;
const int windowHeight = 720;
const std::string windowTitle = "BlockWorld";

int exitWithError(const char* msg) {  // NOLINT
  std::cerr << msg << std::endl;
  glfwTerminate();
  std::cerr << "goodbye" << std::endl;
  return EXIT_FAILURE;
}

static void error_callback(int error, const char* description) {
  std::cerr << "Error: " << error << "\n" << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    std::cerr << "You pressed the e key" << std::endl;
  }
}

std::function<void()> loop;
void main_loop() { loop(); }

int main(void) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) exit(EXIT_FAILURE);

  std::unique_ptr<Window> window =
      Window::createWindow(windowWidth, windowHeight, windowTitle);
  if (window == nullptr) {
    return exitWithError("Failed to create GLFW window\n");
  }

  loop = [&] {
    float ratio;
    int width, height;
    glViewport(0, 0, width, height);
    glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window->nativeWindow.get());
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