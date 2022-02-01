#include "core/BoxGeometry.h"

#include "core/BufferGeometry.h"

namespace app::box_geometry {

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

auto create(vec3 size, const std::vector<vec4> &uv)
    -> std::unique_ptr<BufferGeometry> {
  // std::vector<vec2> uv = {{0.0, 1.0}};
  int uvsize = static_cast<int>(uv.size());

  float x_size = size.x / 2.0F;
  float y_size = size.y / 2.0F;
  float z_size = size.z / 2.0F;
  // xp,xn,yp,yn,zp,zn
  vec4 xp = (uv.empty()) ? vec4{0.0, 0.0, 1.0, 1.0} : uv[0];
  vec4 xn = uv.size() > 1 ? uv[1] : xp;
  vec4 yp = uv.size() > 2 ? uv[2] : xp;
  vec4 yn = uv.size() > 3 ? uv[3] : xp;
  vec4 zp = uv.size() > 4 ? uv[4] : xp;
  vec4 zn = uv.size() > 5 ? uv[5] : xp;

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
       x_size,  y_size,  z_size, xp.x, xp.y, // C
       x_size,  y_size, -z_size, xp.z, xp.y, // H
       x_size, -y_size, -z_size, xp.z, xp.w, // E
       x_size, -y_size, -z_size, xp.z, xp.w, // E
       x_size, -y_size,  z_size, xp.x, xp.w, // B
       x_size,  y_size,  z_size, xp.x, xp.y, // C
      // x negative (Left)
      -x_size,  y_size,  z_size, zn.z, zn.y, // D
      -x_size,  y_size, -z_size, zn.x, zn.y, // G
      -x_size, -y_size, -z_size, zn.x, zn.w, // F
      -x_size, -y_size, -z_size, zn.x, zn.w, // F
      -x_size, -y_size,  z_size, zn.z, zn.w, // A
      -x_size,  y_size,  z_size, zn.z, zn.y, // D
      // y positive (Top)
      -x_size,  y_size, -z_size, yp.x, yp.y, // G
       x_size,  y_size, -z_size, yp.z, yp.y, // H
       x_size,  y_size,  z_size, yp.z, yp.w, // C
       x_size,  y_size,  z_size, yp.z, yp.w, // C
      -x_size,  y_size,  z_size, yp.x, yp.w, // D
      -x_size,  y_size, -z_size, yp.x, yp.y, // G
      // y negative (Bottom)
      -x_size, -y_size, -z_size, yn.x, yn.w, // F
       x_size, -y_size, -z_size, yn.z, yn.w, // E
       x_size, -y_size,  z_size, yn.z, yn.y, // B
       x_size, -y_size,  z_size, yn.z, yn.y, // B
      -x_size, -y_size,  z_size, yn.x, yn.y, // A
      -x_size, -y_size, -z_size, yn.x, yn.w, // F
      // z positive (Front)
      -x_size, -y_size,  z_size, zp.x, zp.w, // A
       x_size, -y_size,  z_size, zp.z, zp.w, // B
       x_size,  y_size,  z_size, zp.z, zp.y, // C
       x_size,  y_size,  z_size, zp.z, zp.y, // C
      -x_size,  y_size,  z_size, zp.x, zp.y, // D
      -x_size, -y_size,  z_size, zp.x, zp.w, // A
      // z negative (Back)
      -x_size, -y_size, -z_size, zn.z, zn.w, // F
       x_size, -y_size, -z_size, zn.x, zn.w, // E
       x_size,  y_size, -z_size, zn.x, zn.y, // H
       x_size,  y_size, -z_size, zn.x, zn.y, // H
      -x_size,  y_size, -z_size, zn.z, zn.y, // G
      -x_size, -y_size, -z_size, zn.z, zn.w, // F

  };
  // clang-format on

  //  std::vector<uint16> indices{
  //      0, 1, 2, 2, 3, 0,  // front
  //      1, 5, 6, 6, 2, 1,  // right
  //      7, 6, 5, 5, 4, 7,  // back
  //      4, 0, 3, 3, 7, 4,  // left
  //      4, 5, 1, 1, 0, 4,  // bottom
  //      3, 2, 6, 6, 7, 3   // top
  //  };

  std::vector<BufferAttribute> attributes{{
      {.type = GL_FLOAT, .count = 3},  // position
      {.type = GL_FLOAT, .count = 2}   // uv
  }};
  auto geometry = make_unique<BufferGeometry>(vertices, attributes);
  return geometry;
}

}  // namespace app::box_geometry