#ifndef BLOCK_WORLD_MESH_H
#define BLOCK_WORLD_MESH_H

#include "BufferGeometry.h"
#include "Camera.h"
#include "Material.h"

namespace block_world {

enum class MeshMode {
  kTriangles,
  kPoints,
  kLines,
};

class Mesh {
 public:
  Mesh() = default;
  Mesh(std::shared_ptr<BufferGeometry> bufferGeometry,
       std::shared_ptr<Material> material) noexcept;
  void render(Camera &camera) const;

 private:
  std::shared_ptr<BufferGeometry> bufferGeometry_{};
  std::shared_ptr<Material> material_{};
  MeshMode mode_{MeshMode::kTriangles};
};

}  // namespace block_world
#endif  // BLOCK_WORLD_MESH_H
