#include "Chunk.h"

#include <utility>

#include "../core/BoxGeometry.h"
#include "BlockMap.h"

namespace app {

constexpr auto size_of_chunk(int x, int y, int z) -> int { return 4; }

Chunk::Chunk() : data_(std::make_shared<ChunkData>()) {
  std::cout << "Chunk()" << std::endl;
}
auto Chunk::size() -> int { return width_ * width_ * height_; };
auto Chunk::data() -> ChunkDataPtr { return data_; };

auto Chunk::get_position_from_index(int index) -> vec3 {
  int y = index / height_;
  int remainder = index % height_;
  int z = remainder / width_;
  int x = remainder % width_;
  return vec3{x, y, z};
}

auto Chunk::get_index_from_position(int x, int y, int z) -> int {
  return y * height_ + z * width_ + x;
}

void Chunk::generate() {
  std::cout << "Chunk::generate()" << std::endl;
  data_->resize(size());
  std::fill(data_->begin(), data_->end(), 0);
  std::cout << "filled=" << data_->size() << std::endl;

  std::cout << "zero? " << data_->at(0) << std::endl;
  for (int i = 0; i < data_->size(); i++) {
    auto pos = get_position_from_index(i);
    std::cout << i << "=(" << pos.x << "," << pos.y << "," << pos.z << ") ";
  }
  std::cout << "done..." << std::endl;
}

ChunkGfx::ChunkGfx(std::shared_ptr<Chunk> chunk,
                   std::shared_ptr<TextureAtlas> atlas,
                   const BlockMap &blockMap)
    : chunk_(chunk), atlas_(atlas) {
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

  std::cout << "before segfault" << std::endl;
  auto data = chunk_->data();
  std::cout << "data=" << data << std::endl;
  auto size = data->size();
  std::cout << "before segfault" << size << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << i << "=";
    auto id = chunk->data()->at(i);
    std::cout << id << ",";
  }

  for (int y = 0; y < kChunkHeight; y++) {
    for (int x = 0; x < kChunkWidth; x++) {
      for (int z = 0; z < kChunkWidth; z++) {
        // Pass in the vector to add the geometry to so we don't have to
        // waste memory creating/destroying
        // app::box_geometry::create_box(all, { .position = ...});

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
