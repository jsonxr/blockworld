#ifndef CORE_VERTEX_H
#define CORE_VERTEX_H

#include "core.h"

namespace app {

struct Vertex {
  vec3 pos{};
  vec3 normal{};
  vec2 uv{};
  //  GLubyte light_level;  // 1 byte (0-15)
  //  vec3 color;           // r,g,b
  //  bool blend;           // 1 byte?? or is it 1 bit?? (GLboolean)
};

}  // namespace app

#endif  // CORE_VERTEX_H
