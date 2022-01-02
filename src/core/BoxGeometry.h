#ifndef BLOCK_WORLD_BOXGEOMETRY_H
#define BLOCK_WORLD_BOXGEOMETRY_H

#include <utility>

#include "BufferGeometry.h"

namespace BlockWorld::BoxGeometry {

auto create(vec3 size) -> std::unique_ptr<BufferGeometry>;

}  // namespace BlockWorld::BoxGeometry

#endif  // BLOCK_WORLD_BOXGEOMETRY_H
