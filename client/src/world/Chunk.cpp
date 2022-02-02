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
    : chunk_(std::move(std::move(chunk))), atlas_(std::move(std::move(atlas))) {
  auto grass_side = atlas_->getRectByName("minecraft:block/grass_block_side");
  auto top = atlas_->getRectByName("minecraft:block/azalea_top");
  auto dirt = atlas_->getRectByName("minecraft:block/dirt");
  if (!grass_side) {
    std::cout << "no grass_side...!!!!!!!!!!!!!!!" << std::endl;
  }

  constexpr int kBlockVerts = 36;
  constexpr int kVertFloats = 5;

  std::vector<BufferAttribute> attributes{{
      {.type = GL_FLOAT, .count = 3},  // position
      {.type = GL_FLOAT, .count = 2}   // uv
  }};
  BufferGeometry all{
      .attributes = std::move(attributes),
  };
  // all.attributes = std::move(attributes);
  all.vertices.reserve(
      static_cast<long>(kChunkSize * kBlockVerts * kVertFloats));

  for (int y = 0; y < kChunkHeight; y++) {
    for (int x = 0; x < kChunkWidth; x++) {
      for (int z = 0; z < kChunkWidth; z++) {
        auto vertices = app::box_geometry::create_box({
            .indexed = true,
            .position = {x, y, z},
            .size = {1, 1, 1},
            .uv_xp = grass_side->uv,
            .uv_xn = grass_side->uv,
            .uv_yp = top->uv,
            .uv_yn = dirt->uv,
            .uv_zp = grass_side->uv,
            .uv_zn = grass_side->uv,
        });

        all.append(*vertices);
      }
    }
  }

  std::cout << "Chunk creating buffer..." << std::endl;
  buffer_ = std::make_unique<BufferGeometryGfx>(all);
  std::cout << "Created buffer" << std::endl;
}

void ChunkGfx::render() {
  // material_->render(camera);
  //   // calculate the model matrix for each object and pass it to shader
  //   before
  //   // drawing
  //   glm::mat4 model = glm::mat4(1.0F);
  //   //model = glm::translate(model, kCubePositions.at(i));
  //   material_->setModelMatrix(model);

  buffer_->render();
}

}  // namespace app
