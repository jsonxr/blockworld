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
  ushort id{};
  std::string name{};
  ushort x{};
  ushort y{};
  ushort width{};
  ushort height{};
  std::filesystem::path path{};
  UV uv{};
};

}  // namespace block_world

#endif  // BLOCK_WORLD_TEXTURES_TEXTURE_RECT_H
