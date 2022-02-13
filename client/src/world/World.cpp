#include "World.h"

#include "Chunk.h"

namespace app {

auto World::getBlock(const ivec3 loc) -> Block * {
  auto chunk_loc =
      ivec3{loc.x * kChunkWidth, loc.y * kChunkHeight, loc.z * kChunkWidth};
  return nullptr;
}

}  // namespace app