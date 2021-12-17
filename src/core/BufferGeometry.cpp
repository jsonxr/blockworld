//
// Created by Jason Rowland on 12/15/21.
//

#include "BufferGeometry.h"

#include <vector>

namespace BlockWorld {

void BufferGeometry::setVertices(std::vector<Vertex> vertices) {
  _vertices = vertices;
}

}  // namespace BlockWorld