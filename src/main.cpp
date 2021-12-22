#include "core.h"
#include "core/BoxGeometry.h"
#include "core/BufferGeometry.h"
#include "core/Camera.h"
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

auto main() -> int {
  glfwSetErrorCallback(error_callback);
  if (glfwInit() == 0) {
    return EXIT_FAILURE;
  }

  Window window{windowTitle, WindowSize{640, 480}};

  if (window.nativeWindow() == nullptr) {
    return exitWithError("Failed to create GLFW window\n");
  }

  auto geometry = BoxGeometry::create({1, 1, 1});

  std::cout << "geometry=" << *geometry << std::endl;
  auto material = std::make_unique<Material>();
  std::cout << "cube1 " << *geometry << std::endl;

  // auto cube = std::make_unique<Mesh>(std::move(geometry),
  // std::move(material));
  auto cube = std::make_unique<Mesh>(std::move(geometry), std::move(material));

  // auto cube = std::make_unique<Mesh>(geometry, material);
  //  std::cout << "Mesh: " << cube.get() << std::endl;
  std::cout << "cube2 " << geometry << std::endl;
  std::cout << "after cube2";
  Scene scene{};
  scene.add(std::move(cube));

  Camera camera{};
  WebGLRenderer renderer{};
  renderer.compile(scene);

  loop = [&] {
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