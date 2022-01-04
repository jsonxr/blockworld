#include "BoxGeometry.h"

#include "BufferGeometry.h"

namespace BlockWorld::BoxGeometry {

constexpr float HALF = 0.5F;

auto create(vec3 size) -> std::unique_ptr<BufferGeometry> {
  std::cout << size[0] << "," << size[1] << "," << size[2] << std::endl;

  std::vector<GLfloat> vertices{
      // Back
      -HALF, -HALF, -HALF, 0.0, 0.0,  // F
      HALF, -HALF, -HALF, 1.0, 0.0,   // E
      HALF, HALF, -HALF, 1.0, 1.0,    // H
      HALF, HALF, -HALF, 1.0, 1.0,    // H
      -HALF, HALF, -HALF, 0.0, 1.0,   // G
      -HALF, -HALF, -HALF, 0.0, 0.0,  // F

      // Front
      -HALF, -HALF, HALF, 0.0, 0.0,  // A
      HALF, -HALF, HALF, 1.0, 0.0,   // B
      HALF, HALF, HALF, 1.0, 1.0,    // C
      HALF, HALF, HALF, 1.0, 1.0,    // C
      -HALF, HALF, HALF, 0.0, 1.0,   // C
      -HALF, -HALF, HALF, 0.0, 0.0,  // A

      // Left
      -HALF, HALF, HALF, 1.0, 0.0,    // D
      -HALF, HALF, -HALF, 1.0, 1.0,   // G
      -HALF, -HALF, -HALF, 0.0, 1.0,  // F
      -HALF, -HALF, -HALF, 0.0, 1.0,  // F
      -HALF, -HALF, HALF, 0.0, 0.0,   // A
      -HALF, HALF, HALF, 1.0, 0.0,    // D

      // Right
      HALF, HALF, HALF, 1.0, 0.0,    // C
      HALF, HALF, -HALF, 1.0, 1.0,   // H
      HALF, -HALF, -HALF, 0.0, 1.0,  // E
      HALF, -HALF, -HALF, 0.0, 1.0,  // E
      HALF, -HALF, HALF, 0.0, 0.0,   // B
      HALF, HALF, HALF, 1.0, 0.0,    // C

      // Bottom
      -HALF, -HALF, -HALF, 0.0, 1.0,  // F
      HALF, -HALF, -HALF, 1.0, 1.0,   // E
      HALF, -HALF, HALF, 1.0, 0.0,    // B
      HALF, -HALF, HALF, 1.0, 0.0,    // B
      -HALF, -HALF, HALF, 0.0, 0.0,   // A
      -HALF, -HALF, -HALF, 0.0, 1.0,  // F

      // Top
      -HALF, HALF, -HALF, 0.0, 1.0,  // G
      HALF, HALF, -HALF, 1.0, 1.0,   // H
      HALF, HALF, HALF, 1.0, 0.0,    // C
      HALF, HALF, HALF, 1.0, 0.0,    // C
      -HALF, HALF, HALF, 0.0, 0.0,   // D
      -HALF, HALF, -HALF, 0.0, 1.0   // G

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