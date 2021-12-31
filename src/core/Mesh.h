#ifndef BLOCKWORLD_MESH_H
#define BLOCKWORLD_MESH_H

#include "BufferGeometry.h"
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
  void render() const;

 private:
  std::shared_ptr<BufferGeometry> _bufferGeometry{};
  std::shared_ptr<Material> _material{};
  MeshMode _mode{MeshMode::triangles};
};

}  // namespace BlockWorld
#endif  // BLOCKWORLD_MESH_H
