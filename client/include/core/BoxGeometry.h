#ifndef BLOCK_WORLD_BOXGEOMETRY_H
#define BLOCK_WORLD_BOXGEOMETRY_H

#include <utility>

#include "BufferGeometry.h"
#include "core/textures/TextureRect.h"

namespace block_world::box_geometry {

auto create(vec3 size,
            const std::vector<UV> &uv = {{{0.0F, 0.0F}, {1.0F, 1.0F}}})
    -> std::unique_ptr<BufferGeometry>;

}  // namespace block_world::box_geometry

#endif  // BLOCK_WORLD_BOXGEOMETRY_H
