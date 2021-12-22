//
// Created by Jason Rowland on 12/19/21.
//

#ifndef BLOCKWORLD_BOXGEOMETRY_H
#define BLOCKWORLD_BOXGEOMETRY_H

#include <utility>

#include "BufferGeometry.h"

namespace BlockWorld::BoxGeometry {

auto create(vec3 size) -> std::unique_ptr<BufferGeometry>;

}  // namespace BlockWorld::BoxGeometry

#endif  // BLOCKWORLD_BOXGEOMETRY_H
