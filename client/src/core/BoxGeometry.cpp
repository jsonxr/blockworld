#include "core/BoxGeometry.h"

#include "core/BufferGeometry.h"

namespace app::box_geometry {

constexpr float kHalf = 0.5F;

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

auto create_geometry(const BoxOptions &options)
    -> std::unique_ptr<BufferGeometry> {
  vec3 p = options.position;
  float x_size = options.size.x / 2.0F;
  float y_size = options.size.y / 2.0F;
  float z_size = options.size.z / 2.0F;
  // xp,xn,yp,yn,zp,zn
  vec4 xp = options.uv_xp;
  vec4 xn = options.uv_xn;
  vec4 yp = options.uv_yp;
  vec4 yn = options.uv_yn;
  vec4 zp = options.uv_zp;
  vec4 zn = options.uv_zn;

  // clang-format off
  std::vector<GLfloat> vertices{
      // x positive (Right)
      p.x+x_size, p.y-y_size, p.z-z_size, xp.z, xp.w, // E
      p.x+x_size, p.y+y_size, p.z-z_size, xp.z, xp.y, // H
      p.x+x_size, p.y+y_size, p.z+z_size, xp.x, xp.y, // C
      p.x+x_size, p.y+y_size, p.z+z_size, xp.x, xp.y, // C
      p.x+x_size, p.y-y_size, p.z+z_size, xp.x, xp.w, // B
      p.x+x_size, p.y-y_size, p.z-z_size, xp.z, xp.w, // E
      // x negative (Left)
      p.x-x_size, p.y+y_size, p.z+z_size, zn.z, zn.y, // D
      p.x-x_size, p.y+y_size, p.z-z_size, zn.x, zn.y, // G
      p.x-x_size, p.y-y_size, p.z-z_size, zn.x, zn.w, // F
      p.x-x_size, p.y-y_size, p.z-z_size, zn.x, zn.w, // F
      p.x-x_size, p.y-y_size, p.z+z_size, zn.z, zn.w, // A
      p.x-x_size, p.y+y_size, p.z+z_size, zn.z, zn.y, // D
      // y positive (Top)
      p.x+x_size, p.y+y_size, p.z+z_size, yp.z, yp.w, // C
      p.x+x_size, p.y+y_size, p.z-z_size, yp.z, yp.y, // H
      p.x-x_size, p.y+y_size, p.z-z_size, yp.x, yp.y, // G
      p.x-x_size, p.y+y_size, p.z-z_size, yp.x, yp.y, // G
      p.x-x_size, p.y+y_size, p.z+z_size, yp.x, yp.w, // D
      p.x+x_size, p.y+y_size, p.z+z_size, yp.z, yp.w, // C
      // y negative (Bottom)
      p.x-x_size, p.y-y_size, p.z-z_size, yn.x, yn.w, // F
      p.x+x_size, p.y-y_size, p.z-z_size, yn.z, yn.w, // E
      p.x+x_size, p.y-y_size, p.z+z_size, yn.z, yn.y, // B
      p.x+x_size, p.y-y_size, p.z+z_size, yn.z, yn.y, // B
      p.x-x_size, p.y-y_size, p.z+z_size, yn.x, yn.y, // A
      p.x-x_size, p.y-y_size, p.z-z_size, yn.x, yn.w, // F
      // z positive (Front)
      p.x-x_size, p.y-y_size, p.z+z_size, zp.x, zp.w, // A
      p.x+x_size, p.y-y_size, p.z+z_size, zp.z, zp.w, // B
      p.x+x_size, p.y+y_size, p.z+z_size, zp.z, zp.y, // C
      p.x+x_size, p.y+y_size, p.z+z_size, zp.z, zp.y, // C
      p.x-x_size, p.y+y_size, p.z+z_size, zp.x, zp.y, // D
      p.x-x_size, p.y-y_size, p.z+z_size, zp.x, zp.w, // A
      // z negative (Back)
      p.x+x_size, p.y+y_size, p.z-z_size, zn.x, zn.y, // H
      p.x+x_size, p.y-y_size, p.z-z_size, zn.x, zn.w, // E
      p.x-x_size, p.y-y_size, p.z-z_size, zn.z, zn.w, // F
      p.x-x_size, p.y-y_size, p.z-z_size, zn.z, zn.w, // F
      p.x-x_size, p.y+y_size, p.z-z_size, zn.z, zn.y, // G
      p.x+x_size, p.y+y_size, p.z-z_size, zn.x, zn.y, // H
  };
  // clang-format on
  // auto result = std::make_unique<std::vector<GLfloat>>(std::move(vertices));

  // return result;

  std::vector<BufferAttribute> attributes{{
      {.type = GL_FLOAT, .count = 3},  // position
      {.type = GL_FLOAT, .count = 2}   // uv
  }};
  BufferGeometry geometry{
      .attributes = std::move(attributes),
      .vertices = std::move(vertices),
  };
  auto result = std::make_unique<BufferGeometry>(std::move(geometry));
  return result;
}

auto create_geometry_indexed(const BoxOptions &options)
    -> std::unique_ptr<BufferGeometry> {
  vec3 p = options.position;
  float x_size = options.size.x / 2.0F;
  float y_size = options.size.y / 2.0F;
  float z_size = options.size.z / 2.0F;
  // xp,xn,yp,yn,zp,zn
  vec4 xp = options.uv_xp;
  vec4 xn = options.uv_xn;
  vec4 yp = options.uv_yp;
  vec4 yn = options.uv_yn;
  vec4 zp = options.uv_zp;
  vec4 zn = options.uv_zn;

  // clang-format off
  std::vector<GLfloat> vertices{
      // x positive (Right) - EHC, CBE (0,1,2,2,3,0)
      p.x+x_size, p.y-y_size, p.z-z_size, xp.z, xp.w, // E 0
      p.x+x_size, p.y+y_size, p.z-z_size, xp.z, xp.y, // H 1
      p.x+x_size, p.y+y_size, p.z+z_size, xp.x, xp.y, // C 2
      p.x+x_size, p.y-y_size, p.z+z_size, xp.x, xp.w, // B 3
      // x negative (Left) - DGF, FAD (4,5,6,6,7,4)
      p.x-x_size, p.y+y_size, p.z+z_size, zn.z, zn.y, // D 4
      p.x-x_size, p.y+y_size, p.z-z_size, zn.x, zn.y, // G 5
      p.x-x_size, p.y-y_size, p.z-z_size, zn.x, zn.w, // F 6
      p.x-x_size, p.y-y_size, p.z+z_size, zn.z, zn.w, // A 7
      // y positive (Top) - CHG, GDC (8,9,10,10,11,8)
      p.x+x_size, p.y+y_size, p.z+z_size, yp.z, yp.w, // C 8
      p.x+x_size, p.y+y_size, p.z-z_size, yp.z, yp.y, // H 9
      p.x-x_size, p.y+y_size, p.z-z_size, yp.x, yp.y, // G 10
      p.x-x_size, p.y+y_size, p.z+z_size, yp.x, yp.w, // D 11
      // y negative (Bottom) - FEB, BAF (12,13,14,14,15,12)
      p.x-x_size, p.y-y_size, p.z-z_size, yn.x, yn.w, // F 12
      p.x+x_size, p.y-y_size, p.z-z_size, yn.z, yn.w, // E 13
      p.x+x_size, p.y-y_size, p.z+z_size, yn.z, yn.y, // B 14
      p.x-x_size, p.y-y_size, p.z+z_size, yn.x, yn.y, // A 15
      // z positive (Front) - ABC, CDA (16,17,18,18,19,16)
      p.x-x_size, p.y-y_size, p.z+z_size, zp.x, zp.w, // A 16
      p.x+x_size, p.y-y_size, p.z+z_size, zp.z, zp.w, // B 17
      p.x+x_size, p.y+y_size, p.z+z_size, zp.z, zp.y, // C 18
      p.x-x_size, p.y+y_size, p.z+z_size, zp.x, zp.y, // D 19
      // z negative (Back) - HEF, FGH (20,21,22,22,23,20)
      p.x+x_size, p.y+y_size, p.z-z_size, zn.x, zn.y, // H 20
      p.x+x_size, p.y-y_size, p.z-z_size, zn.x, zn.w, // E 21
      p.x-x_size, p.y-y_size, p.z-z_size, zn.z, zn.w, // F 22
      p.x-x_size, p.y+y_size, p.z-z_size, zn.z, zn.y, // G 23
  };

  std::vector<int> elements{
      // x positive (Right) - EHC, CBE
       0,  1,  2,  2,  3,  0,
      // x negative (Left) - DGF, FAD
       4,  5,  6,  6,  7,  4,
      // y positive (Top) - CHG, GDC
       8,  9, 10, 10, 11,  8,
      // y negative (Bottom) - FEB, BAF
      12, 13, 14, 14, 15, 12,
      // z positive (Front) - ABC, CDA 
      16, 17, 18, 18, 19, 16,
      // z negative (Back) - HEF, FGH 
      20, 21, 22, 22, 23, 20,
  };
  // clang-format on

  std::vector<BufferAttribute> attributes{{
      {.type = GL_FLOAT, .count = 3},  // position
      {.type = GL_FLOAT, .count = 2}   // uv
  }};
  BufferGeometry geometry{
      .attributes = std::move(attributes),
      .vertices = std::move(vertices),
      .elements = std::move(elements),
  };
  auto result = std::make_unique<BufferGeometry>(std::move(geometry));
  return result;
}

auto create_box(const BoxOptions &options) -> std::unique_ptr<BufferGeometry> {
  if (options.indexed) {
    return create_geometry_indexed(options);
  }
  return create_geometry(options);
}

auto create_buffer_geometry(const BoxOptions &options)
    -> std::unique_ptr<BufferGeometryGfx> {
  auto geometry = create_box(options);

  BufferGeometryGfx gfx{*geometry};

  auto geometry2 = std::make_unique<BufferGeometryGfx>(std::move(gfx));
  return geometry2;
}

}  // namespace app::box_geometry