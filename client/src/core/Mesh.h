#ifndef APP_MESH_H
#define APP_MESH_H

#include "BufferGeometry.h"
#include "Camera.h"
#include "Material.h"

namespace app {

enum class MeshMode {
  kTriangles,
  kPoints,
  kLines,
};

class Mesh {
 public:
  Mesh() = default;
  Mesh(std::shared_ptr<BufferGeometryGfx> bufferGeometry,
       std::shared_ptr<Material> material) noexcept;
  void render(Camera &camera) const;

 private:
  std::shared_ptr<BufferGeometryGfx> bufferGeometry_{};
  std::shared_ptr<Material> material_{};
  MeshMode mode_{MeshMode::kTriangles};
};

}  // namespace app
#endif  // APP_MESH_H
