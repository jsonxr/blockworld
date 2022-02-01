#ifndef APP_TEXTURES_PIXEL_H
#define APP_TEXTURES_PIXEL_H

#include <vector>

#include "core.h"

namespace app {

struct Pixel {
  uint8 r, g, b, a;
};
constexpr int kChannels = sizeof(Pixel) / sizeof(uint8);

}  // namespace app

#endif  // APP_TEXTURES_PIXEL_H
