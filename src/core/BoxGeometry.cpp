#include "BoxGeometry.h"

#include "BufferGeometry.h"

namespace BlockWorld::BoxGeometry {

auto create(vec3 size) -> std::unique_ptr<BufferGeometry> {
  std::cout << size[0] << "," << size[1] << "," << size[2] << std::endl;

  std::vector<float> vertices{
      // positions        // colors         // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
  };

  //  std::vector<float> vertices{
  //      // positions        // texture coords
  //      0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
  //      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
  //      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
  //      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
  //  };
  std::vector<u32> indices{
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  std::unique_ptr<BufferGeometry> geometry =
      make_unique<BufferGeometry>(vertices, indices);
  return geometry;
}

}  // namespace BlockWorld::BoxGeometry