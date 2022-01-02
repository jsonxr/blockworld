#ifndef BLOCK_WORLD_MESH_H
#define BLOCK_WORLD_MESH_H

#include "BufferGeometry.h"
#include "Camera.h"
#include "Material.h"

namespace BlockWorld {

enum class MeshMode {
  triangles,
  points,
  lines,
};

class Mesh {
 public:
  Mesh() = default;
  Mesh(std::shared_ptr<BufferGeometry> bufferGeometry,
       std::shared_ptr<Material> material) noexcept;
  void render(Camera &camera) const;

 private:
  std::shared_ptr<BufferGeometry> _bufferGeometry{};
  std::shared_ptr<Material> _material{};
  MeshMode _mode{MeshMode::triangles};
};

}  // namespace BlockWorld
#endif  // BLOCK_WORLD_MESH_H
