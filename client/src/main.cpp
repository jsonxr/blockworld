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
#include "world/Chunk.h"

using namespace app;
// using app::Material;
// using app::Mesh;
// using app::Scene;
// using app::TextureAtlas;
// using app::WebGLRenderer;
// using app::Window;
// using app::WindowSize;

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

// auto getFiles(const std::string &path) -> std::vector<std::filesystem::path>
// {
//   std::vector<std::filesystem::path> files_in_directory;
//   std::copy(std::filesystem::directory_iterator(path),
//             std::filesystem::directory_iterator(),
//             std::back_inserter(files_in_directory));
//   std::sort(files_in_directory.begin(), files_in_directory.end());
//   return files_in_directory;
// }

// auto main2() -> int {
//   auto atlas = TextureAtlas::loadFromDirectory(
//       "minecraft:block/", "/minecraft/textures/block", app::Size{512, 1024});
//   atlas->save("test.png");
//   return 0;
// }

auto main() -> int {  // NOLINT(bugprone-exception-escape)
  if (glfwInit() == 0) {
    return EXIT_FAILURE;
  }

  std::string path = get_executable_path();
  std::cout << "path: " << path.c_str() << std::endl;

  glfwSetErrorCallback(error_callback);

  Window window{kWindowTitle, WindowSize{app::kDefaultWindowWidth,
                                         app::kDefaultWindowHeight}};

  if (window.nativeWindow() == nullptr) {
    return exitWithError("Failed to create GLFW window\n");
  }

  auto atlas = app::TextureAtlas::loadFromDirectory(
      "minecraft:block/", "/minecraft/textures/block", app::Size{512, 1024});
  atlas->save("test.png");

  auto material = std::make_shared<Material>(atlas);
  auto chunk = std::make_shared<Chunk>();
  ChunkGfx chunk_gfx{chunk, atlas};

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
    app::Window::pollEvents();
    window.process(delta_time);

    glClearColor(0.F, 0.F, 0.F, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glm::mat4 model = glm::mat4(1.0F);
    material->setModelMatrix(model);
    material->render(window.camera());

    chunk_gfx.render();

    glfwSwapBuffers(window.nativeWindow());
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
  glfwTerminate();
  return EXIT_SUCCESS;
}
