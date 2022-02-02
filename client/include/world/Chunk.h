#ifndef APP_WORLD_CHUNK_H
#define APP_WORLD_CHUNK_H

#include "core.h"
#include "core/BufferGeometry.h"
#include "core/textures/TextureAtlas.h"

namespace app {

struct Vertex {
  vec3 pos_{};
  vec2 uv{};
};

constexpr int kChunkWidth = 16;
constexpr int kChunkHeight = 256;
constexpr int kChunkSize = kChunkWidth * kChunkWidth * kChunkHeight;

class Chunk {
 public:
  Chunk() = default;

 private:
  std::array<int16, kChunkSize> data_{};
};

class ChunkGfx {
 public:
  ChunkGfx(std::shared_ptr<Chunk> chunk, std::shared_ptr<TextureAtlas> atlas);
  void render();

 private:
  std::shared_ptr<Chunk> chunk_;
  std::unique_ptr<BufferGeometryGfx> buffer_;
  std::shared_ptr<TextureAtlas> atlas_;
  std::unique_ptr<std::array<Vertex, kChunkSize>> vertices_;
  GLuint glVao_{0};
  GLuint glVbo_{0};
};

}  // namespace app

#endif  // APP_WORLD_CHUNK_H
