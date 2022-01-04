#include "core.h"
#include "core/BoxGeometry.h"
#include "core/BufferGeometry.h"
#include "core/Camera.h"
#include "core/Input.h"
#include "core/Scene.h"
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

void processInput(Window& win, Camera& camera, double deltaTime) {
  auto window = win.nativeWindow();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::RIGHT, deltaTime);
  }
}

auto main() -> int {
  if (glfwInit() == 0) {
    return EXIT_FAILURE;
  }

  glfwSetErrorCallback(error_callback);

  Window window{windowTitle, WindowSize{DEFAULT_WIDTH, DEFAULT_HEIGHT}};

  if (window.nativeWindow() == nullptr) {
    return exitWithError("Failed to create GLFW window\n");
  }

  auto geometry = BoxGeometry::create({1, 1, 1});
  auto material =
      std::make_shared<Material>("/textures/block/grass_block_side.png");
  auto cube = std::make_shared<Mesh>(std::move(geometry), std::move(material));
  //
  Scene scene{};
  scene.add(std::move(cube));
  //
  Camera camera{{vec3(0.0F, 0.0F, 3.0F)}};
  // Camera camera(vec3(0.0f, 0.0f, 3.0f));
  WebGLRenderer renderer{};

  // timing
  GLdouble deltaTime{};
  GLdouble lastFrame{};

  loop = [&] {
    // per-frame time logic
    // --------------------
    GLdouble currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(window, camera, deltaTime);
    // camera.process_mouse_movement(Input::mouseX, Input::mouseY);

    // or... loop = [&window, &scene, &camera, &renderer] {
    renderer.render(window, scene, camera);
    glfwPollEvents();
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, true);
#else
  while (!window.shouldClose()) {
    loop();
  }
#endif

  window.close();

  glfwTerminate();
  exit(EXIT_SUCCESS);
}