#ifndef APP_WORLD_CHUNK_H
#define APP_WORLD_CHUNK_H

#include "core.h"
#include "core/textures/TextureAtlas.h"

namespace app {

struct Vertex {
  vec3 pos_{};
  vec2 uv{};
};

constexpr int kChunkWidth = 16;
constexpr int kChunkHeight = 256;
constexpr int kChunkSize = kChunkWidth * kChunkWidth * kChunkHeight;

struct Chunk {
  Chunk();
  std::array<int16, kChunkSize> data_{};
};

struct ChunkGfx {
 public:
  ChunkGfx(std::shared_ptr<Chunk> chunk, std::shared_ptr<TextureAtlas> atlas);
  void render();

 private:
  std::shared_ptr<Chunk> chunk_;
  std::shared_ptr<TextureAtlas> atlas_;
  std::unique_ptr<std::array<Vertex, kChunkSize>> vertices_;
};

}  // namespace app

#endif  // APP_WORLD_CHUNK_H
