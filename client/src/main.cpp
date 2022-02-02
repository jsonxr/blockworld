#include <set>

#include "core.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/textures/TextureAtlas.h"
#include "core/Window.h"
#include "importer/MinecraftImporter.h"
#include "utils/executable.h"
#include "utils/Tracer.h"
#include "world/BlockMap.h"
#include "world/Chunk.h"
#include "utils/memory.h"
#include <boost/format.hpp>


using namespace app;

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

std::function<void()> loop;
void main_loop() { loop(); }

auto main2() -> int {  // NOLINT(bugprone-exception-escape)
  if (glfwInit() == 0) {
    return EXIT_FAILURE;
  }

  std::string path = utils::get_executable_path();
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

  BlockMap block_map{};

  auto material = std::make_shared<Material>(atlas);
  auto chunk = std::make_shared<Chunk>();
  chunk->generate();
  ChunkGfx chunk_gfx{chunk, atlas, block_map};

  // WebGLRenderer renderer{};

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

auto main_import() -> int {
  importer::MinecraftImporter map{};
  map.load();
  map.get_block("minecraft:block/oak_stairs");

  return 0;
}

auto main() -> int {
  cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50 << endl;
  utils::display_sizeof_values();
  auto total_memory = utils::getTotalSystemMemory();
  std::cout << "memory: " << utils::prettyBytes(total_memory) << "("<< total_memory << ")"<< std::endl;
  //test_memory();
  // main_import();
  main2();
  return 0;
}
