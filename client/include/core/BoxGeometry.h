#ifndef APP_BOXGEOMETRY_H
#define APP_BOXGEOMETRY_H

#include <utility>

#include "BufferGeometry.h"
#include "core/textures/TextureRect.h"

namespace app::box_geometry {

auto create(vec3 size,
            const std::vector<UV> &uv = {{{0.0F, 0.0F}, {1.0F, 1.0F}}})
    -> std::unique_ptr<BufferGeometry>;

}  // namespace app::box_geometry

#endif  // APP_BOXGEOMETRY_H
