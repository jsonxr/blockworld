#ifndef APP_WORLD_CHUNK_H
#define APP_WORLD_CHUNK_H

#include "../core.h"
#include "../core/BufferGeometry.h"
#include "../core/textures/TextureAtlas.h"

namespace app {

class BlockMap;

struct Vertex {
  vec3 pos_{};
  vec2 uv{};
};

constexpr int kChunkWidth = 16;
constexpr int kChunkHeight = 256;
constexpr int kChunkSize = kChunkWidth * kChunkWidth * kChunkHeight;

using ChunkData = std::vector<int16>;
using ChunkDataPtr = std::shared_ptr<ChunkData>;

class Chunk {
 public:
  Chunk();
  auto data() -> ChunkDataPtr;
  auto size() -> int;
  void generate();
  auto get_position_from_index(int index) -> vec3;
  auto get_index_from_position(int x, int y, int z) -> int;

 private:
  int width_{kChunkWidth};
  int height_{kChunkHeight};
  ChunkDataPtr data_{};
};

class ChunkGfx {
 public:
  ChunkGfx(std::shared_ptr<Chunk> chunk, std::shared_ptr<TextureAtlas> atlas,
           const BlockMap &blockMap);
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
