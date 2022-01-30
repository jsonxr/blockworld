#include "core/BoxGeometry.h"

#include "core/BufferGeometry.h"

namespace block_world::box_geometry {

constexpr float kHalf = 0.5F;

/*
       G--------H
      /        /|
     /        / |
(u) D--------C  |
    |  |     |  |
    |  F --  |  E
    | /      | /
    |        |/
    A--------B (v)

*/

auto create(vec3 size, const std::vector<UV> &uv)
    -> std::unique_ptr<BufferGeometry> {
  // std::vector<vec2> uv = {{0.0, 1.0}};
  int uvsize = uv.size();

  float x_size = size.x / 2.0F;
  float y_size = size.y / 2.0F;
  float z_size = size.z / 2.0F;
  // xp,xn,yp,yn,zp,zn
  UV xp = (uv.empty()) ? UV{{0.0, 0.0}, {1.0, 1.0}} : uv[0];
  UV xn = uv.size() > 1 ? uv[1] : xp;
  UV yp = uv.size() > 2 ? uv[2] : xp;
  UV yn = uv.size() > 3 ? uv[3] : xp;
  UV zp = uv.size() > 4 ? uv[4] : xp;
  UV zn = uv.size() > 5 ? uv[5] : xp;

  // float: 4 bytes
  // int: 4 bytes
  //
  // vertex = 5 floats (x,y,z, u.x, u.v) = 20 bytes
  // 36vertex = 36 * 20 = 720
  // ...720 bytes
  //
  // Indexed:

  // 4verts for each face = 24 verts = 480 bytes
  // int elements = 36 = 144 bytes
  // ...624 bytes

  // clang-format off
  std::vector<GLfloat> vertices{
      // x positive (Right)
       x_size,  y_size,  z_size, xp.u.x, xp.u.y, // C
       x_size,  y_size, -z_size, xp.v.x, xp.u.y, // H
       x_size, -y_size, -z_size, xp.v.x, xp.v.y, // E
       x_size, -y_size, -z_size, xp.v.x, xp.v.y, // E
       x_size, -y_size,  z_size, xp.u.x, xp.v.y, // B
       x_size,  y_size,  z_size, xp.u.x, xp.u.y, // C
      // x negative (Left)
      -x_size,  y_size,  z_size, zn.v.x, zn.u.y, // D
      -x_size,  y_size, -z_size, zn.u.x, zn.u.y, // G
      -x_size, -y_size, -z_size, zn.u.x, zn.v.y, // F
      -x_size, -y_size, -z_size, zn.u.x, zn.v.y, // F
      -x_size, -y_size,  z_size, zn.v.x, zn.v.y, // A
      -x_size,  y_size,  z_size, zn.v.x, zn.u.y, // D
      // y positive (Top)
      -x_size,  y_size, -z_size, yp.u.x, yp.u.y, // G
       x_size,  y_size, -z_size, yp.v.x, yp.u.y, // H
       x_size,  y_size,  z_size, yp.v.x, yp.v.y, // C
       x_size,  y_size,  z_size, yp.v.x, yp.v.y, // C
      -x_size,  y_size,  z_size, yp.u.x, yp.v.y, // D
      -x_size,  y_size, -z_size, yp.u.x, yp.u.y, // G
      // y negative (Bottom)
      -x_size, -y_size, -z_size, yn.u.x, yn.v.y, // F
       x_size, -y_size, -z_size, yn.v.x, yn.v.y, // E
       x_size, -y_size,  z_size, yn.v.x, yn.u.y, // B
       x_size, -y_size,  z_size, yn.v.x, yn.u.y, // B
      -x_size, -y_size,  z_size, yn.u.x, yn.u.y, // A
      -x_size, -y_size, -z_size, yn.u.x, yn.v.y, // F
      // z positive (Front)
      -x_size, -y_size,  z_size, zp.u.x, zp.v.y, // A
       x_size, -y_size,  z_size, zp.v.x, zp.v.y, // B
       x_size,  y_size,  z_size, zp.v.x, zp.u.y, // C
       x_size,  y_size,  z_size, zp.v.x, zp.u.y, // C
      -x_size,  y_size,  z_size, zp.u.x, zp.u.y, // D
      -x_size, -y_size,  z_size, zp.u.x, zp.v.y, // A
      // z negative (Back)
      -x_size, -y_size, -z_size, zn.v.x, zn.v.y, // F
       x_size, -y_size, -z_size, zn.u.x, zn.v.y, // E
       x_size,  y_size, -z_size, zn.u.x, zn.u.y, // H
       x_size,  y_size, -z_size, zn.u.x, zn.u.y, // H
      -x_size,  y_size, -z_size, zn.v.x, zn.u.y, // G
      -x_size, -y_size, -z_size, zn.v.x, zn.v.y, // F

  };
  // clang-format on

  //  std::vector<u32> indices{
  //      0, 1, 2, 2, 3, 0,  // front
  //      1, 5, 6, 6, 2, 1,  // right
  //      7, 6, 5, 5, 4, 7,  // back
  //      4, 0, 3, 3, 7, 4,  // left
  //      4, 5, 1, 1, 0, 4,  // bottom
  //      3, 2, 6, 6, 7, 3   // top
  //  };

  auto geometry = make_unique<BufferGeometry>(vertices);
  return geometry;
}

}  // namespace block_world::box_geometry