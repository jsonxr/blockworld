#ifndef APP_BOXGEOMETRY_H
#define APP_BOXGEOMETRY_H

#include <utility>

#include "BufferGeometry.h"
#include "../core.h"

namespace app::box_geometry {
struct BoxOptions {
  bool indexed{};
  vec3 position{0.0, 0.0, 0.0};
  vec3 size{1.0, 1.0, 1.0};
  vec4 uv_xp{0.0, 0.0, 1.0, 1.0};
  vec4 uv_xn{0.0, 0.0, 1.0, 1.0};
  vec4 uv_yp{0.0, 0.0, 1.0, 1.0};
  vec4 uv_yn{0.0, 0.0, 1.0, 1.0};
  vec4 uv_zp{0.0, 0.0, 1.0, 1.0};
  vec4 uv_zn{0.0, 0.0, 1.0, 1.0};
};

auto create_box(const BoxOptions &options) -> std::unique_ptr<BufferGeometry>;

auto create_buffer_geometry(const BoxOptions &options)
    -> std::unique_ptr<BufferGeometryGfx>;

}  // namespace app::box_geometry

#endif  // APP_BOXGEOMETRY_H
