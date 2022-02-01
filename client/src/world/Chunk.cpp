#include "world/Chunk.h"

#include <utility>

#include "core/BoxGeometry.h"

namespace app {

// auto Chunk::generate() -> std::unique_ptr<std::vector<Vertex>> {
//   for (int y = 0; y < kChunkHeight; y++) {
//     for (int x = 0; x < kChunkWidth; x++) {
//       for (int z = 0; z < kChunkWidth; z++) {
//       }
//     }
//   }
//   return nullptr;
// }

ChunkGfx::ChunkGfx(std::shared_ptr<Chunk> chunk,
                   std::shared_ptr<TextureAtlas> atlas)
    : chunk_(std::move(std::move(chunk))),
      atlas_(std::move(std::move(atlas))) {}

void ChunkGfx::render() {
  auto grass_side = atlas_->getRectByName("minecraft:block/grass_block_side");
  auto top = atlas_->getRectByName("minecraft:block/azalea_top");
  auto dirt = atlas_->getRectByName("minecraft:block/dirt");
  if (!grass_side) {
    std::cout << "no grass_side...!!!!!!!!!!!!!!!" << std::endl;
  }

  auto geometry = app::box_geometry::create(
      {1, 1, 1}, {grass_side->uv, grass_side->uv, top->uv, dirt->uv,
                  grass_side->uv, grass_side->uv});

  // std::unique_ptr<std::vector<Vertex>> vertices_;
}

void render();

}  // namespace app
