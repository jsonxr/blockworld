#include "BoxGeometry.h"

#include "BufferGeometry.h"

namespace BlockWorld::BoxGeometry {

auto create(vec3 size) -> std::unique_ptr<BufferGeometry> {
  std::cout << size[0] << "," << size[1] << "," << size[2] << std::endl;

  std::vector<GLfloat> vertices{
      // Back
      -0.5, -0.5, -0.5, 0.0, 0.0,  // F
      0.5, -0.5, -0.5, 1.0, 0.0,   // E
      0.5, 0.5, -0.5, 1.0, 1.0,    // H
      0.5, 0.5, -0.5, 1.0, 1.0,    // H
      -0.5, 0.5, -0.5, 0.0, 1.0,   // G
      -0.5, -0.5, -0.5, 0.0, 0.0,  // F

      // Front
      -0.5, -0.5, 0.5, 0.0, 0.0,  // A
      0.5, -0.5, 0.5, 1.0, 0.0,   // B
      0.5, 0.5, 0.5, 1.0, 1.0,    // C
      0.5, 0.5, 0.5, 1.0, 1.0,    // C
      -0.5, 0.5, 0.5, 0.0, 1.0,   // C
      -0.5, -0.5, 0.5, 0.0, 0.0,  // A

      // Left
      -0.5, 0.5, 0.5, 1.0, 0.0,    // D
      -0.5, 0.5, -0.5, 1.0, 1.0,   // G
      -0.5, -0.5, -0.5, 0.0, 1.0,  // F
      -0.5, -0.5, -0.5, 0.0, 1.0,  // F
      -0.5, -0.5, 0.5, 0.0, 0.0,   // A
      -0.5, 0.5, 0.5, 1.0, 0.0,    // D

      // Right
      0.5, 0.5, 0.5, 1.0, 0.0,    // C
      0.5, 0.5, -0.5, 1.0, 1.0,   // H
      0.5, -0.5, -0.5, 0.0, 1.0,  // E
      0.5, -0.5, -0.5, 0.0, 1.0,  // E
      0.5, -0.5, 0.5, 0.0, 0.0,   // B
      0.5, 0.5, 0.5, 1.0, 0.0,    // C

      // Bottom
      -0.5, -0.5, -0.5, 0.0, 1.0,  // F
      0.5, -0.5, -0.5, 1.0, 1.0,   // E
      0.5, -0.5, 0.5, 1.0, 0.0,    // B
      0.5, -0.5, 0.5, 1.0, 0.0,    // B
      -0.5, -0.5, 0.5, 0.0, 0.0,   // A
      -0.5, -0.5, -0.5, 0.0, 1.0,  // F

      // Top
      -0.5, 0.5, -0.5, 0.0, 1.0,  // G
      0.5, 0.5, -0.5, 1.0, 1.0,   // H
      0.5, 0.5, 0.5, 1.0, 0.0,    // C
      0.5, 0.5, 0.5, 1.0, 0.0,    // C
      -0.5, 0.5, 0.5, 0.0, 0.0,   // D
      -0.5, 0.5, -0.5, 0.0, 1.0   // G

  };

  //  std::vector<u32> indices{
  //      0, 1, 2, 2, 3, 0,  // front
  //      1, 5, 6, 6, 2, 1,  // right
  //      7, 6, 5, 5, 4, 7,  // back
  //      4, 0, 3, 3, 7, 4,  // left
  //      4, 5, 1, 1, 0, 4,  // bottom
  //      3, 2, 6, 6, 7, 3   // top
  //  };

  std::unique_ptr<BufferGeometry> geometry =
      make_unique<BufferGeometry>(vertices);
  return geometry;
}

}  // namespace BlockWorld::BoxGeometry