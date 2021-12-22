//
// Created by Jason Rowland on 12/19/21.
//

#include "BoxGeometry.h"

#include "BufferGeometry.h"

namespace BlockWorld::BoxGeometry {

auto create(vec3 size) -> std::unique_ptr<BufferGeometry> {
  std::cout << size[0] << "," << size[1] << "," << size[2] << std::endl;
  std::vector<float> vertices{
      0.5F,  0.5F,  0.0F,  // top right
      0.5f,  -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f   // top left
  };
  std::vector<u32> indices{
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  std::unique_ptr<BufferGeometry> geometry =
      make_unique<BufferGeometry>(vertices, indices);
  return geometry;
}

}  // namespace BlockWorld::BoxGeometry