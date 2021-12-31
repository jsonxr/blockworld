#include "Mesh.h"

#include <cmath>
#include <regex>

namespace BlockWorld {

Mesh::Mesh(std::shared_ptr<BufferGeometry> bufferGeometry,
           std::shared_ptr<Material> material) noexcept
    : _bufferGeometry(std::move(bufferGeometry)),
      _material(std::move(material)) {
  std::cout << "Mesh(b,m) verts=" << _bufferGeometry->getVertices().size()
            << std::endl;
}

void Mesh::render() const {
  _material->render();
  _bufferGeometry->render();
}

}  // namespace BlockWorld
