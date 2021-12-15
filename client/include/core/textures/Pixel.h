#ifndef BLOCK_WORLD_TEXTURES_PIXEL_H
#define BLOCK_WORLD_TEXTURES_PIXEL_H

#include <vector>

#include "core.h"

namespace block_world {

struct Pixel {
  uint8 r, g, b, a;
};
constexpr int kChannels = sizeof(Pixel) / sizeof(uint8);

}  // namespace block_world

#endif  // BLOCK_WORLD_TEXTURES_PIXEL_H
