#include <fmt/format.h>

#include <regex>
#include <set>

#include "core.h"
#include "core/Assets.h"
#include "core/BoxGeometry.h"
#include "core/BufferGeometry.h"
#include "core/Camera.h"
#include "core/Input.h"
#include "core/Scene.h"
#include "core/Window.h"
#include "core/textures/TextureAtlas.h"
#include "core/textures/TextureRect.h"
#include "core/webgl/WebGLRenderer.h"
#include "utils.h"
// using namespace block_world;
using block_world::Camera;
using block_world::CameraMovement;
using block_world::Material;
using block_world::Mesh;
using block_world::Scene;
using block_world::WebGLRenderer;
using block_world::Window;
using block_world::WindowSize;

constexpr auto kWindowTitle = "BlockWorld";

int exitWithError(const char *msg) {  // NOLINT
  std::cerr << msg << std::endl;
  glfwTerminate();
  std::cerr << "goodbye" << std::endl;
  return EXIT_FAILURE;
}

static void error_callback(int error, const char *description) {
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

void processInput(Window &win, Camera &camera, double deltaTime) {
  auto *window = win.nativeWindow();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::kForward, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::kBackward, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::kLeft, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.process_keyboard(CameraMovement::kRight, deltaTime);
  }
}

auto getFiles(const std::string &path) -> std::vector<std::filesystem::path> {
  std::vector<std::filesystem::path> files_in_directory;
  std::copy(std::filesystem::directory_iterator(path),
            std::filesystem::directory_iterator(),
            std::back_inserter(files_in_directory));
  std::sort(files_in_directory.begin(), files_in_directory.end());
  return files_in_directory;
}

auto main2() -> int {
  auto atlas = block_world::TextureAtlas::loadFromDirectory(
      "minecraft:block/", "/minecraft/textures/block",
      block_world::Size{512, 1024});
  atlas->save("test.png");
  return 0;
}

auto main() -> int {  // NOLINT(bugprone-exception-escape)
  if (glfwInit() == 0) {
    return EXIT_FAILURE;
  }

  std::string path = get_executable_path();
  std::cout << "path: " << path.c_str() << std::endl;

  glfwSetErrorCallback(error_callback);

  Window window{kWindowTitle, WindowSize{block_world::kDefaultWindowWidth,
                                         block_world::kDefaultWindowHeight}};

  if (window.nativeWindow() == nullptr) {
    return exitWithError("Failed to create GLFW window\n");
  }

  auto atlas = block_world::TextureAtlas::loadFromDirectory(
      "minecraft:block/", "/minecraft/textures/block",
      block_world::Size{512, 1024});
  auto grass_side =
      atlas->getRectByName("minecraft:block/grass_block_side.png");
  auto top = atlas->getRectByName("minecraft:block/azalea_top.png");
  auto dirt = atlas->getRectByName("minecraft:block/dirt.png");
  if (!grass_side) {
    std::cout << "no grass_side...!!!!!!!!!!!!!!!" << std::endl;
  }

  // xp,xn,yp,yn,zp,zn
  auto geometry = block_world::box_geometry::create(
      {1, 1, 1}, {grass_side->uv, grass_side->uv, top->uv, dirt->uv,
                  grass_side->uv, grass_side->uv});

  // block_world::TextureArray textures{};
  // textures.add("/textures/block/grass_block_side.png");
  // textures.add("/textures/block/dirt.png");
  std::cout << "material..." << std::endl;
  auto material = std::make_shared<Material>(std::move(atlas));
  std::cout << "cube..." << std::endl;
  auto cube = std::make_shared<Mesh>(std::move(geometry), std::move(material));
  std::cout << "scene..." << std::endl;
  //
  Scene scene{};
  scene.add(std::move(cube));

  std::cout << "camera..." << std::endl;
  //
  Camera camera{{vec3(0.0F, 0.0F, 3.0F)}};

  std::cout << "renderer..." << std::endl;
  // Camera camera(vec3(0.0f, 0.0f, 3.0f));
  WebGLRenderer renderer{};

  // timing
  GLdouble delta_time{};
  GLdouble last_frame{};

  loop = [&] {
    // per-frame time logic
    // --------------------
    GLdouble current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    // input
    // -----
    processInput(window, camera, delta_time);
    // camera.process_mouse_movement(input::mouse_x, input::mouse_y);

    // or... loop = [&window, &scene, &camera, &renderer] {
    block_world::WebGLRenderer::render(window, scene, camera);
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
  return 0;
}
