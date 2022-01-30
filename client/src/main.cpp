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
using block_world::Material;
using block_world::Mesh;
using block_world::Scene;
using block_world::TextureAtlas;
using block_world::WebGLRenderer;
using block_world::Window;
using block_world::WindowSize;

constexpr auto kWindowTitle = "BlockWorld";

auto exitWithError(const char *msg) -> int {
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

// void processInput(Window &win, Camera &camera, double deltaTime) {
//   auto *window = win.nativeWindow();

//   float sensitivity = 0.1f;
//   float mx = block_world::input::mouse_x;
//   float my = block_world::input::mouse_y;
//   mx *= sensitivity;
//   my *= sensitivity;

//   camera.orientation.x += my;
//   camera.orientation.y += mx;

//   if (camera.orientation.x > 89.0f) camera.orientation.x = 89.0f;
//   if (camera.orientation.x < -89.0f) camera.orientation.x = -89.0f;

//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//     glfwSetWindowShouldClose(window, 1);
//   }

//   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//     camera.process_keyboard(CameraMovement::kForward, deltaTime);
//   }
//   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//     camera.process_keyboard(CameraMovement::kBackward, deltaTime);
//   }
//   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//     camera.process_keyboard(CameraMovement::kLeft, deltaTime);
//   }
//   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//     camera.process_keyboard(CameraMovement::kRight, deltaTime);
//   }
// }

auto getFiles(const std::string &path) -> std::vector<std::filesystem::path> {
  std::vector<std::filesystem::path> files_in_directory;
  std::copy(std::filesystem::directory_iterator(path),
            std::filesystem::directory_iterator(),
            std::back_inserter(files_in_directory));
  std::sort(files_in_directory.begin(), files_in_directory.end());
  return files_in_directory;
}

auto main2() -> int {
  auto atlas = TextureAtlas::loadFromDirectory("minecraft:block/",
                                               "/minecraft/textures/block",
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
  atlas->save("test.png");
  auto grass_side = atlas->getRectByName("minecraft:block/grass_block_side");
  auto top = atlas->getRectByName("minecraft:block/azalea_top");
  auto dirt = atlas->getRectByName("minecraft:block/dirt");
  if (!grass_side) {
    std::cout << "no grass_side...!!!!!!!!!!!!!!!" << std::endl;
  }

  // xp,xn,yp,yn,zp,zn
  auto geometry = block_world::box_geometry::create(
      {1, 1, 1}, {grass_side->uv, grass_side->uv, top->uv, dirt->uv,
                  grass_side->uv, grass_side->uv});

  auto material = std::make_shared<Material>(std::move(atlas));
  auto cube = std::make_shared<Mesh>(std::move(geometry), std::move(material));
  //
  Scene scene{};
  scene.add(std::move(cube));

  // Camera camera{{vec3(0.0, 0.0, 3.0)}};
  // camera.set_position({0.0, 0.0, 1.0});
  // camera.set_fov(45.0);
  // camera.set_orientation({0.0, 0.0, 0.0});

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
    window.process(delta_time);

    // input.process(camera, delta_time);
    // processInput(window, camera, delta_time);
    // camera.process_mouse_movement(input::mouse_x, input::mouse_y);

    // or... loop = [&window, &scene, &camera, &renderer] {
    block_world::WebGLRenderer::render(window, scene, window.camera());
    block_world::Window::pollEvents();
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, true);
#else
  while (!window.shouldClose() &&
         !window.input().isKeyPressed(GLFW_KEY_ESCAPE)) {
    loop();
  }
#endif

  window.close();

  return EXIT_SUCCESS;
}
