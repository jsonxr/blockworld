#ifndef BLOCK_WORLD_TEXTURES_TEXTURE_H
#define BLOCK_WORLD_TEXTURES_TEXTURE_H

#include <vector>

#include "core.h"

namespace block_world {

struct Texture {
 public:
  int id{};
  std::string filename;
  int x{};
  int y{};
  int width{};
  int height{};
  unsigned char *raw_pixels_ = nullptr;

  // Copy: not supported
  Texture() = default;
  Texture(const Texture &other) = default;        // copy constructor
  auto operator=(const Texture &other) = delete;  // copy assignment
  // Move
  Texture(Texture &&other) noexcept
      : id(std::exchange(other.id, 0)),
        filename(std::exchange(other.filename, "")),
        width(std::exchange(other.width, 0)),
        height(std::exchange(other.height, 0)),
        x(std::exchange(other.x, 0)),
        y(std::exchange(other.y, 0)),
        raw_pixels_(std::exchange(other.raw_pixels_, nullptr)){};
  auto operator=(Texture &&other) noexcept -> Texture & {
    std::swap(id, other.id);
    std::swap(filename, other.filename);
    std::swap(width, other.width);
    std::swap(height, other.height);
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(raw_pixels_, other.raw_pixels_);
    return *this;
  };
};

}  // namespace block_world

#endif  // BLOCK_WORLD_TEXTURES_TEXTURE_H
