//
// Created by Jason Rowland on 12/15/21.
//

#include "BufferGeometry.h"

#include <iostream>
#include <utility>
#include <vector>

namespace BlockWorld {

BufferGeometry::BufferGeometry(std::vector<float> vertices,
                               std::vector<u32> indices)
    : _vertices(std::move(vertices)), _indices(std::move(indices)) {
  std::cout << "BufferGeometry size=" << _vertices.size() << std::endl;
}

auto operator<<(std::ostream& out, const BufferGeometry& geometry)
    -> std::ostream& {
  out << "verts=" << geometry.getVertices().size();
  return out;
}

}  // namespace BlockWorld
