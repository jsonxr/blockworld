//
// Created by Jason Rowland on 12/15/21.
//

#ifndef BLOCKWORLD_BUFFERGEOMETRY_H
#define BLOCKWORLD_BUFFERGEOMETRY_H

#include <array>
#include <vector>

namespace BlockWorld {

struct Vertex {
  std::array<float, 4> color;
  std::array<float, 3> position;
};

class BufferGeometry {
 public:
  static std::shared_ptr<BufferGeometry> create(std::string title);
  void setVertices(std::vector<Vertex> vertices);
  std::vector<Vertex> _vertices;
};

}  // namespace BlockWorld
#endif  // BLOCKWORLD_BUFFERGEOMETRY_H
