#ifndef BLOCK_WORLD_TEXTURES_TEXTURE_RECT_H
#define BLOCK_WORLD_TEXTURES_TEXTURE_RECT_H

#include <filesystem>
#include <vector>

#include "core.h"

namespace block_world {

struct UV {
 public:
  vec2 u;
  vec2 v;
};

struct TextureRect {
 public:
  uint16 id{};
  std::string name{};
  uint16 x{};
  uint16 y{};
  uint16 width{};
  uint16 height{};
  std::filesystem::path path{};
  UV uv{};
};

}  // namespace block_world

#endif  // BLOCK_WORLD_TEXTURES_TEXTURE_RECT_H
